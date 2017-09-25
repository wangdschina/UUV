#pragma once

#include "PacketizedTcp.h"
#include "Poco/Mutex.h"
#include "ROV_Control.h"

#include "PacketizedUdp.h"

using Poco::FastMutex;

class CNetTcpEventHandler : public IPacketizedTcpClientEvent
{
public:
	CNetTcpEventHandler();
	~CNetTcpEventHandler();
	
	virtual int OnRecvPacket(unsigned char* byteStream);
	virtual int OnGetSendPacket(unsigned char**byteStream,int *datalen);
	virtual void OnCloseConnection();
	virtual void OnError(std::string strDisplayText);

public:
	ROV_Control rov_control;
};

class CNetUdpEventHandler : public IPacketizedUdpClientEvent
{
public:
	CNetUdpEventHandler();
	~CNetUdpEventHandler();
	
	virtual int OnRecvPacket(unsigned char *byteStream,int datelen);
	virtual void OnCloseConnection();
	virtual void OnError(std::string strDisplayText);
};

