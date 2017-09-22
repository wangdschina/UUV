#pragma once
#include "packetizedudp.h"
#include <mutex>

#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Thread.h"

using Poco::Net::DatagramSocket;
using Poco::Net::SocketAddress;
using Poco::Thread;


class CPacketizedUdpImpl : 
	public IPacketizedUdpClient, 
	public Poco::Runnable
{
public:
	CPacketizedUdpImpl(void);
	~CPacketizedUdpImpl(void);

	virtual bool Connect(const char* szHostAddress, unsigned short unPort);
	virtual void Disconnect();
	virtual void SetClientListener(IPacketizedUdpClientEvent* pClientEvent);
	virtual bool Send();

	virtual void run();

private:
	IPacketizedUdpClientEvent* m_pClientEvent;

private:
	DatagramSocket* m_pDatagramSocket;
	Thread m_thread;

	std::mutex m_mtx;	//	同步接收和断开连接
};

