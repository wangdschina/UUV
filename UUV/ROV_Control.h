#pragma once
#include "UUV_Command_Param.h"
#include <windows.h>
typedef struct       //命令传输数据体,78字节
{
	UUV_U8 data_start[8];		//数据开始标志
	Attitude ATT;				//姿态控制数据 20字节
	UUV_U16 power;					//板载设备供电控制	0开启，1关闭 bit0:摄像头，bit1:POE,bit2:外挂CAN总线
	CAM camdata[1];			//摄像头数据		2×12字节
	MOTOR motor;			//	六个电机的转速控制
	Extraman extraman;		//机械手数据		8字节	
	UUV_U8 reserved[3];			//保留的数据
	UUV_U8 OSD_Set;				//OSD控制开关
	UUV_U16 Send_Cnt;			//发送计数++(测试通讯)
	UUV_U16 crc16;				//crc校验值，不含开始和结尾的标志
	UUV_U8 data_end[8];			//数据结尾				//数据长度80字节，含头尾
}ROV_CMD;


//====================================================================================================
typedef struct      //状态传输数据体，114字节 8+20+14(2*7)+24(12*2)+4(2*2)+8+16+4+6+2+8=14
{
	UUV_U8 data_start[8];		//数据开始标志

	Attitude ATT;				//姿态控制数据 
	UUV_U16 power;					//板载设备供电控制	0开启，1关闭 bit0:摄像头，bit1:POE,bit2:外挂CAN总线
	
	UUV_S16 Temperature;		//舱外水温，其他温度信息通过can总线获取
	UUV_U16 Salinity;			//盐度，来自电导率传感器，百分比
	UUV_S16 depth;				//深度，单位cm，0-100米范围 U16
	UUV_S16 Temperature_in;		//机内温度
	UUV_U16 pressure_in;			//机内压力 kPa
	UUV_U16 humidity_in;				//机内湿度，百分比

	CAM camdata[1];			//摄像头数据			2×12字节
	MOTOR motor;			//	六个电机的转速控制
	UUV_S16 llumination[2];	//摄像头照度信息
	Extraman extraman;		//机械手数据			8字节
	POWER p_inf;			//电源信息				16字节
	//HI_U8 ERROR[4];			//系统错误状态
	UUV_U16 Send_Packet_Num;	//遥控器发给F407的包总数
	UUV_U16 Send_Packet_Loss_Num;	//遥控器发给F407的丢包总数
	UUV_U16 Receive_Cnt;		//ROV发送计数(测试通讯)
	UUV_U16 crc16;				//crc校验值，不含开始和结尾的标志
	UUV_U8 data_end[8];			//数据结尾
}ROV_STAT,*PROV_STAT;


const int Depth_Offset=100;
class ROV_Control
{
public:
	ROV_Control(void);
	~ROV_Control();
	ROV_CMD CMD_RCtoROV;      //RC将要发给ROV的命令
	ROV_STAT STAT_ROVtoRC;      //ROV发回来的数据，解析之后

	void ROV_CMD_Init();
		/******************************************************************************
	 * Function: RC_CMD_Assemble_New - 遥控器发送数据创建
	 * Description: 
	 *     遥控器发送数据创建 
	 * Input: 
	 * Output: 
	 * Returns: 
	 * 
	 * revision history:
	 *     version 1.0 
	******************************************************************************/
	void ROV_RC_CMD_Assemble(void);
	void Set_Reset_Flag(bool flag);
	bool Get_Reset_Flag();

	public:
	short m_temproll;//横滚
	short m_tempitch;//俯仰
	short m_temyaw;//航向
	short m_temspeed;//前进速度
	short m_temdepth;//目标深度
	short m_camerapitch;//云台俯仰
	short m_camerarotate;//云台旋转
	short m_camerazoom;//镜头变倍
	short m_camerafocus;//镜头聚焦
	unsigned char m_leftlight;//镜头聚焦
	unsigned char m_rightlight;//镜头聚焦
	short m_left_forward_motor;//左前电机
	short m_left_backward_motor;//左前电机
	short m_right_forward_motor;//左前电机
	short m_right_backward_motor;//左前电机
	short m_left_H_motor;//左前电机
	short m_right_H_motor;//左前电机

private:
	 bool m_need_reset;
	HANDLE m_Mutex;
};


