#include "stdafx.h"
#include "PacketizedTcpImpl.h"
#include <mstcpip.h>

// 缓冲区长度 (1024*8) 之所以为什么设置8K，也是一个江湖上的经验值
// 如果确实客户端发来的每组数据都比较少，那么就设置得小一些，省内存
const int MAX_BUFFER_LEN = 512;//houmb

/*
数据包结构说明
字节序号			数据内容说明				说明
0、1、2、3		包验证标志				默认包验证标志为 0x5678
4、5、6、7		包实体内容的大小			本包长度为从包指令字节的下一个字节开始，到包尾的所有字节数
*/
const int MAX_PACKET_BODY_LEN = 1024 * 1024;
const int PACKET_HEADER_LEN = 8;
const DWORD PACKET_FLAG = 0x5678;

CPacketizedTcpClient* g_tcpClient = nullptr;

//////////////////////////////////////////////////////////////////////////
//	Client
CPacketizedTcpClient::CPacketizedTcpClient()
{
	g_tcpClient = this;

	m_netState = E_NET_DISCONNED;

	m_bManualDisconn = true;
	m_pClientEvent = NULL;
	m_pStreamSocket = NULL;
	datapackage = (unsigned char *)malloc(DATA_TOTAL_LEN);

	m_taskmanager.cancelAll();
	m_taskmanager.start(new CNetReconnTask("ReconnTask"));
}

CPacketizedTcpClient::~CPacketizedTcpClient()
{
	m_pClientEvent = NULL;
	this->Disconnect();
	while (m_thread.isRunning())
	{
		Sleep(10);
	}
	
	if(datapackage!=NULL)
	{
		free(datapackage);
		datapackage = NULL;
	}

	m_taskmanager.cancelAll();
	//delete this;
}

bool CPacketizedTcpClient::Connect(const char* szHostAddress, unsigned short unPort)
{
	try
	{
		m_netState = E_NET_CONNING;
		if (m_pStreamSocket)	/*	已打开直接返回	*/
		{
			m_netState = E_NET_CONNED;
			return true;
		}

		m_sockAddr = SocketAddress(szHostAddress, unPort);
		m_pStreamSocket = new StreamSocket();//(m_sockAddr);
		if (!m_pStreamSocket)
		{
			LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("创建SOCKET失败"));
			return false;
		}
		// 设置连接超时时间
		Timespan timeout(1, 0);
		m_pStreamSocket->connect(m_sockAddr, timeout);
		m_pStreamSocket->setKeepAlive(true);
		struct tcp_keepalive keepin;
		struct tcp_keepalive keepout;
		keepin.onoff = 1;
		// 超过30S没有数据，就发送探测包
		keepin.keepalivetime = 30*1000;
		// 每1S发送1包探测报文，发10次没有回应，就断开
		keepin.keepaliveinterval = 1000;
		DWORD dwBytes = 0;
		int nRet = ::WSAIoctl(m_pStreamSocket->impl()->sockfd(), SIO_KEEPALIVE_VALS, &keepin, sizeof(keepin),
			&keepout, sizeof(keepout), &dwBytes, NULL, NULL);
		if (nRet == SOCKET_ERROR)
		{
			LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("WSAIoctl failed: %d"), WSAGetLastError());
			return false;
		}

		m_thread.start(*this);

		m_netState =  E_NET_CONNED;

		FastMutex::ScopedLock lock(m_mciMutex);
		m_bManualDisconn = true;
		
		return true;
	}
	catch (Poco::Exception& exc)
	{
		if (m_pClientEvent != NULL)
		{
			m_pClientEvent->OnError(exc.displayText());

			FastMutex::ScopedLock lock(m_mciMutex);
			m_bManualDisconn = false;
		}
		Disconnect();
	}
	m_netState = E_NET_DISCONNED;
	return false;
}

void CPacketizedTcpClient::Disconnect()
{
	m_netState = E_NET_DISCONNING;
	if (m_pStreamSocket != NULL)
	{
		m_pStreamSocket->close();
		delete m_pStreamSocket;
		m_pStreamSocket = NULL;
	}
	m_netState = E_NET_DISCONNED;

	listqueue.clearQueue();
}

void CPacketizedTcpClient::SetClientListener(IPacketizedTcpClientEvent* pClientEvent)
{
	m_pClientEvent = pClientEvent;
}

bool CPacketizedTcpClient::Send()
{
	if (m_pStreamSocket != NULL)
	{
		try
		{
			/*CByteStream packetStream;
			packetStream.Write(PACKET_FLAG);
			packetStream.Write(byteStream.GetNumberOfBytesUsed());
			packetStream.Write(byteStream.GetData(), byteStream.GetNumberOfBytesUsed());*/
			unsigned char *pbyteStream=NULL;
			int Datelen=0;
			m_pClientEvent->OnGetSendPacket(&pbyteStream,&Datelen);
			if((pbyteStream!=NULL)&&(Datelen==ROV_SEND_DATALEN))
			{
				m_pStreamSocket->sendBytes(pbyteStream,Datelen);
			}
			else
			{
				LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("发送数据异常"));
			}
			return true;
		}
		catch (Poco::Exception& exc)
		{
			if (m_pClientEvent != NULL)
			{
				m_pClientEvent->OnError(exc.displayText());
			}
		}
	}
	return false;
}

void CPacketizedTcpClient::run()
{
	try
	{
		while (m_pStreamSocket != NULL)
		{
			char szBuffer[MAX_BUFFER_LEN]={0};
			int nRcved = m_pStreamSocket->receiveBytes(szBuffer, sizeof(szBuffer));
			if (nRcved <= 0)
			{
				this->Disconnect();
				if (m_pClientEvent != NULL)
				{
					m_pClientEvent->OnCloseConnection();
				}
				FastMutex::ScopedLock lock(m_mciMutex);
				m_bManualDisconn = false;
				break;
			}
			else
			{
				for(int i=0;i<nRcved;i++)
				{
					listqueue.enQueue(szBuffer[i]);
				}
				if(ROV_Recv_procrec(&listqueue,datapackage))//解析出一个ROV状态包
				{ // 读取错误
					//	MessageBox("获得一包数据");
					if (m_pClientEvent != NULL)
					{
						m_pClientEvent->OnRecvPacket(datapackage);
					}
					// printf("%d",Prov_stat->ATT.roll);
				}
				Send();
				//	if (dwFlag != 0x5354524301000000)
				//	{ // 包验证标志错误
				//		m_byteStream.Reset();
				//		if (m_pClientEvent != NULL)
				//		{
				//			m_pClientEvent->OnError("包验证标志错误");
				//		}
				//		break;
				//	}

				//	int nLength;
				//	if (!m_byteStream.Read(nLength))
				//	{ // 读取错误
				//		m_byteStream.Reset();
				//		if (m_pClientEvent != NULL)
				//		{
				//			m_pClientEvent->OnError("读取错误");
				//		}
				//		break;
				//	}
				//	if (nLength > MAX_PACKET_BODY_LEN)
				//	{ // 包实体内容的大小超出限制
				//		m_byteStream.Reset();
				//		if (m_pClientEvent != NULL)
				//		{
				//			m_pClientEvent->OnError("包实体内容的大小超出限制");
				//		}
				//		break;
				//	}

				//	if ((m_byteStream.GetReadOffset() + nLength) > m_byteStream.GetNumberOfBytesUsed())
				//	{ // 包体不全, 恢复本次最初读取点，等待下次处理
				//		m_byteStream.SetReadOffset(unByteReadOffset);
				//		break;
				//	}

				//	if (m_pClientEvent != NULL)
				//	{
				//		CByteStream byteStream(m_byteStream.GetData() + m_byteStream.GetReadOffset(), nLength, false);
				//		m_pClientEvent->OnRecvPacket(byteStream);
				//	}

				//	m_byteStream.SetReadOffset(m_byteStream.GetReadOffset() + nLength);
				//}

				// 清理已读取的内存
				//if (m_byteStream.GetReadOffset() > 0 && m_byteStream.GetNumberOfBytesUsed() >= m_byteStream.GetReadOffset())
				//{
				//	if (m_byteStream.GetNumberOfBytesUsed() == m_byteStream.GetReadOffset())
				//	{
				//		m_byteStream.Reset();
				//	}
				//	else
				//	{
						// 把不完整的重拷到前面供下次读
				//		CByteStream byteStream(m_byteStream.GetData() + m_byteStream.GetReadOffset(), m_byteStream.GetNumberOfBytesUsed() - m_byteStream.GetReadOffset(), true);
				//		m_byteStream.Reset();
				//		m_byteStream.Write(byteStream.GetData(), byteStream.GetNumberOfBytesUsed());
				//	}
				//}
			}
		}
	}
	catch (Poco::Net::ConnectionResetException& exc)
	{
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("捕获异常:%s"), CStringUtil::AnsiToTStr(exc.displayText()).c_str());

		this->Disconnect();
		if (m_pClientEvent != NULL)
		{
			m_pClientEvent->OnCloseConnection();
		}
		FastMutex::ScopedLock lock(m_mciMutex);
		m_bManualDisconn = false;
	}
	catch (Poco::TimeoutException& exc)
	{
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("捕获异常:%s"), CStringUtil::AnsiToTStr(exc.displayText()).c_str());		

		this->Disconnect();
		if (m_pClientEvent != NULL)
		{
			m_pClientEvent->OnCloseConnection();
		}
		FastMutex::ScopedLock lock(m_mciMutex);
		m_bManualDisconn = false;
	}
	catch (Poco::Exception& exc)
	{
		if (m_pClientEvent != NULL)
		{
			m_pClientEvent->OnError(exc.displayText());
		}
	}
}

E_NET_STATE CPacketizedTcpClient::State()
{
	FastMutex::ScopedLock lock(m_mciMutex);

	return m_netState;
}

SocketAddress CPacketizedTcpClient::GetSockAddr( void )
{
	return m_sockAddr;
}


//////////////////////////////////////////////////////////////////////////



