#include "stdafx.h"
#include "BaseFunc.h"
#include "NetEventHandler.h"
#include "ROVSharkMax.h"


CNetTcpEventHandler::CNetTcpEventHandler(void)
{
//houmb
	memset((unsigned char*)&rov_control.CMD_RCtoROV,0,sizeof(rov_control.CMD_RCtoROV));
	 rov_control.ROV_CMD_Init ();
}

CNetTcpEventHandler::~CNetTcpEventHandler(void)
{
}

int  CNetTcpEventHandler::OnGetSendPacket(unsigned char** byteStream,int* pdatalen)
{
	if(pdatalen==NULL)
		return -1;
	rov_control.ROV_RC_CMD_Assemble();//重组控制数据
	*byteStream=(unsigned char*)(&rov_control.CMD_RCtoROV);
	*pdatalen=sizeof(rov_control.CMD_RCtoROV);
	return 0;
}
int CNetTcpEventHandler::OnRecvPacket(unsigned char* byteStream)
{
	//unsigned char packetType;
	//houmb
	//LogMsg(WT_EVENTLOG_INFORMATION_TYPE, _T("Get a ROV data package"));
	rov_control.STAT_ROVtoRC=*((ROV_STAT*)byteStream);
	if (CROVSharkMax::m_pHandler)
	{
		UUV_RESULT pResult = (UUV_RESULT)((PUUV_STAT)(byteStream+8));
		CROVSharkMax::m_pHandler(pResult);
	}

	return 0;
}

void CNetTcpEventHandler::OnCloseConnection()
{
	LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("检测到服务器连接关闭"));
}

void CNetTcpEventHandler::OnError(std::string strDisplayText)
{
	LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("OnError:%s"), CStringUtil::AnsiToTStr(strDisplayText).c_str());
}

CNetUdpEventHandler::CNetUdpEventHandler()
{

}

CNetUdpEventHandler::~CNetUdpEventHandler()
{

}

int CNetUdpEventHandler::OnRecvPacket( unsigned char *byteStream,int datelen )
{
	
	if (CROVSharkMax::m_pUSBLHandler)
	{
		UUV_RESULT pResult = (UUV_RESULT)((PUUV_USBL_INFO)(byteStream+datelen-35));
		CROVSharkMax::m_pUSBLHandler(pResult);
	}
	return 0;
}

void CNetUdpEventHandler::OnCloseConnection()
{
	LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("检测到服务器连接关闭[USBL]"));
}

void CNetUdpEventHandler::OnError( std::string strDisplayText )
{
	LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("OnError:%s[USBL]"), CStringUtil::AnsiToTStr(strDisplayText).c_str());
}
