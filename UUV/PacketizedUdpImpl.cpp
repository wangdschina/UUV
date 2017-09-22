#include "stdafx.h"
#include "PacketizedUdpImpl.h"

#include "Poco/Timespan.h"
using Poco::Timespan;

const int MAX_BUFFER_LEN = 512;

const char* LOCAL_ADDR = "127.0.0.1";
const unsigned short LOCAL_PORT = 8080;

CPacketizedUdpImpl::CPacketizedUdpImpl(void) : 
	m_pClientEvent(NULL), 
	m_pDatagramSocket(NULL)
{
	
}


CPacketizedUdpImpl::~CPacketizedUdpImpl(void)
{
	m_pClientEvent = NULL;
	this->Disconnect();
}

bool CPacketizedUdpImpl::Connect( const char* szHostAddress, unsigned short unPort )
{
	this->Disconnect();
	if (m_pDatagramSocket == NULL)
	{
		m_pDatagramSocket = new DatagramSocket;
	}
	m_pDatagramSocket->setReceiveTimeout(Timespan(1, 0));
	m_pDatagramSocket->bind(SocketAddress(LOCAL_ADDR, LOCAL_PORT));
	m_pDatagramSocket->connect(SocketAddress(szHostAddress, unPort));

	m_thread.start(*this);
	return true;
}

void CPacketizedUdpImpl::Disconnect()
{
	std::lock_guard<std::mutex> lck(m_mtx);
	if (m_pDatagramSocket != NULL)
	{
		m_pDatagramSocket->close();
		delete m_pDatagramSocket;
		m_pDatagramSocket = NULL;
	}
	while (m_thread.isRunning())
	{
		//Sleep(10);
		m_thread.join();
	}
}

void CPacketizedUdpImpl::SetClientListener( IPacketizedUdpClientEvent* pClientEvent )
{
	this->m_pClientEvent = pClientEvent;
}

bool CPacketizedUdpImpl::Send()
{
	if (m_pDatagramSocket != NULL)
	{
		try
		{
			char buf[MAX_BUFFER_LEN] = { 0x00 };
			m_pDatagramSocket->sendBytes(buf, MAX_BUFFER_LEN);
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

void CPacketizedUdpImpl::run()
{
	while (true)
	{
		try
		{
			if (m_pDatagramSocket == NULL)
			{
				break;
			}
			std::lock_guard<std::mutex> lck(m_mtx);
			if (m_pDatagramSocket == NULL)
			{
				break;
			}

#if defined(DEBUG) || defined(_DEBUG)
			/*	for test	*/
			static bool b = false;
			if (!b)
			{
				Send();
				b = !b;
			}
			/*	end	*/
#endif

			char szBuffer[MAX_BUFFER_LEN];
			int nRecv = m_pDatagramSocket->receiveBytes(szBuffer, sizeof(szBuffer));
			if (nRecv <= 0)
			{
				//this->Disconnect();
				if (m_pClientEvent != NULL)
				{
					m_pClientEvent->OnCloseConnection();
				}
				break;
			}
			else
			{
				if (m_pClientEvent != NULL)
				{
					m_pClientEvent->OnRecvPacket((unsigned char*)szBuffer);
				}
			}
		}
		catch (Poco::Net::ConnectionResetException& exc)
		{
			LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("捕获异常:%s"), CStringUtil::AnsiToTStr(exc.displayText()).c_str());
			//this->Disconnect();
			if (m_pClientEvent != NULL)
			{
				m_pClientEvent->OnCloseConnection();
			}
		}
		catch (Poco::TimeoutException& exc)
		{
			LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("捕获异常:%s"), CStringUtil::AnsiToTStr(exc.displayText()).c_str());
			//this->Disconnect();
			if (m_pClientEvent != NULL)
			{
				m_pClientEvent->OnCloseConnection();
			}
		}
		catch (Poco::Exception& exc)
		{
			if (m_pClientEvent != NULL)
			{
				m_pClientEvent->OnError(exc.displayText());
			}
		}
	}
}
