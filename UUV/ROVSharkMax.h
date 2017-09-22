#pragma once

#include "rov.h"
#include "NetEventHandler.h"
#include "DirectUtility.h"
#include "ToolTask.h"

#include "Poco/TaskManager.h"

using Poco::TaskManager;

class CROVSharkMax : public CROV
{
public:
	CROVSharkMax(void);
	~CROVSharkMax(void);

	bool UUV_RegHandler(UUVHandler pHandler);
	bool UUV_RegVideoHandler(UUVVideoFrame pVideoHandler);
	bool UUV_Get(UUV_COMMAND strCommand, UUV_RESULT& pResult);
	bool UUV_Set(UUV_COMMAND strCommand, UUV_PARAM	param);

private:
	bool Net_Open(UUV_PARAM param);
	bool Net_Close(void);
	bool Net_State(UUV_RESULT& pResult);

public:
	bool VideoStream_Open();
	bool VideoStream_Close();

private:
	//added by houmb
	bool Attitude_Roll_Set( UUV_PARAM param );
	bool Attitude_Pitch_Set( UUV_PARAM param );
	bool Attitude_Yaw_Set( UUV_PARAM param );
	bool Forward_Backward_Speed_Set( UUV_PARAM param );
	bool Yaw_Control_Pattern_Set( UUV_PARAM param );
	bool Navigation_Pattern_Set( UUV_PARAM param );
	bool Target_Depth_Set( UUV_PARAM param );
	bool Camera_Pitch_Set( UUV_PARAM param );
	bool Camera_Rotate_Set( UUV_PARAM param );
	bool Camera_Zoom_Set( UUV_PARAM param );
	bool Camera_Focus_Set( UUV_PARAM param );
	bool Light_Value_Set( UUV_PARAM param );
	bool Motor_Speed_Set( UUV_PARAM param );
	bool External_Power_Set( UUV_PARAM param );
	bool Work_Pattern_Set( UUV_PARAM param );
	bool Camera_Osd_Set( UUV_PARAM param );
	bool Power_ConsumMode_Set( UUV_PARAM param );
	bool System_Power_Set( UUV_PARAM param );//系统软重启
	bool Manipulator_Operation_Set( UUV_PARAM param );//机械手操作
public:
	static UUVHandler		m_pHandler;
	static UUVVideoFrame	m_pVideoHandler;

private:
	std::shared_ptr<IPacketizedTcpClient> m_spTcpClient;
	CNetTcpEventHandler m_tcpClientNetEventHandler;

	std::shared_ptr<IPacketizedUdpClient> m_spUdpClient;
	CNetUdpEventHandler m_udpClientNetEventHandler;

private:
	TaskManager m_taskManager;

public:
	mutable FastMutex m_mciMutex;
	unsigned int m_unCount;

public:
	static CDirectUtility m_dxUtility;
	static HWND m_hWnd;
};

extern CROVSharkMax* g_pRovSharkMax;

