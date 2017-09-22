#pragma once

#include "PacketizedTcp.h"
#include "ROV_DataParse.h"

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"
#include "Poco/Task.h"
#include "Poco/TaskManager.h"

using Poco::Net::StreamSocket;
using Poco::Net::SocketAddress;
using Poco::TaskManager;
using Poco::Task;
using Poco::Thread;
using Poco::Timespan;
using Poco::TimeoutException;
using Poco::FastMutex;

const unsigned char ROV_SEND_DATALEN=78;


class CNetReconnTask;

class CPacketizedTcpClient : public Poco::Runnable, public IPacketizedTcpClient
{
public:
	CPacketizedTcpClient();
	~CPacketizedTcpClient();

	virtual bool Connect(const char* szHostAddress, unsigned short unPort);
	virtual void Disconnect();
	virtual void SetClientListener(IPacketizedTcpClientEvent* pClientEvent);
	virtual bool Send();

	virtual E_NET_STATE State();

	virtual void run(); 

public:
	SocketAddress GetSockAddr(void);

public:
	IPacketizedTcpClientEvent* m_pClientEvent;

	mutable FastMutex m_mciMutex;

	
	bool m_bManualDisconn;

	ListQueue listqueue;
	E_NET_STATE m_netState;
	unsigned char *datapackage;

private:
	TaskManager m_taskmanager;

private:
	SocketAddress m_sockAddr;
	StreamSocket* m_pStreamSocket;
	Thread m_thread;
};
extern CPacketizedTcpClient* g_tcpClient;

class CNetReconnTask : public Poco::Task
{
public:
	CNetReconnTask(const std::string& name) : Task(name)
	{};
	~CNetReconnTask(){};

	void runTask()
	{
		while (!isCancelled())
		{
			if (g_tcpClient && !g_tcpClient->m_bManualDisconn && g_tcpClient->m_pClientEvent)
			{
				g_tcpClient->Disconnect();
				g_tcpClient->Connect(g_tcpClient->GetSockAddr().host().toString().c_str(), g_tcpClient->GetSockAddr().port());
			}
			
			Thread::sleep(1000);
		}
	}
};


