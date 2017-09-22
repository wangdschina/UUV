/** 
*  Copyright (c) 2017, 天津深之蓝海洋设备科技有限公司(http://www.deepinfar.com/) 
*  All rights reserved. 
* 
*  @file        UUV_Command_Param.h 
*  @author      wangds
*  @email		dengsheng.wang@deepinfar.com
*  @date        2017/05/11 17:02 
* 
*  @brief       定义UUV命令对应的参数结构 
*  @note        字符集均使用 Unicode 字符集 
* 
*  @version 
*    - v1.0
*/  

#ifndef UUV_Command_Param_h__
#define UUV_Command_Param_h__


/** 当前版本字符集只采用Unicode字符集 */ 
#if defined(UNICODE) || defined(_UNICODE)
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif


/** 命令参数 */ 
typedef void*	UUV_PARAM;


/** 命令结果 */ 
typedef void*	UUV_RESULT;


/** 定义简单的别名 */ 
typedef unsigned char           UUV_U8;
typedef unsigned short          UUV_U16;
typedef unsigned int            UUV_U32;

typedef signed char             UUV_S8;
typedef short                   UUV_S16;
typedef int					    UUV_S32;


/** 构造UUV类型 */ 
enum E_UUV_TYPE
{
	E_ROV_SHARK_MAX = 0x01,		///< 白鲨MAX
};


/** 网络状态 */ 
enum E_NET_STATE
{
	E_NET_CONNING		= 0x01,		///< 连接中
	E_NET_CONNED		= 0x02,		///< 已连接
	E_NET_DISCONNING	= 0x04,		///< 断开中
	E_NET_DISCONNED		= 0x08		///< 已断开
};


/** 网络打开 */ 
typedef struct tagUUVNETOPEN 
{
	tstring			strIP;	///< 网络IP
	UUV_U32 		nPort;	///< 网络端口号
	HWND			hWnd;	///< 显示视频的窗口句柄 NULL或无效窗口句柄为不显示

	tagUUVNETOPEN()
	{
		strIP = _T("192.168.99.10");
		nPort = 5001;
		hWnd = NULL;
	}
} UUVNETOPEN, *PUUVNETOPEN;


/** 灯光设置 */ 
typedef struct tagUUVLIGHT
{
	UUV_U8 lightindex;				///< 本体灯的索引 0代表左灯，1代表右灯
	UUV_U8		lum;				///< 亮度值 取值范围[0-100]
} UUVLIGHT_T, *PUUVLIGHT_T;


/** 推进器索引枚举 */ 
typedef enum 
{
	V_L_F_MOTORINDEX	= 0x50,			///< 垂直方向左前电机索引
	V_L_B_MOTORINDEX	= 0x51,			///< 垂直方向左后电机索引
	V_R_B_MOTORINDEX	= 0x52,			///< 垂直方向右后电机索引
	V_R_F_MOTORINDEX	= 0x53,			///< 垂直方向右前电机索引
	H_L_MOTORINDEX		= 0x58,			///< 水平方向左电机索引
	H_R_MOTORINDEX		= 0x59,			///< 垂直方向右电机索引

} UUVMOTORINDEX;


/** 推进器信息结构体 */ 
typedef struct tagUUVMOTOR
{
	UUV_U8 motorindex;				///< 电机索引，取值范围为[0x50,0x51,0x52,0x53,0x58,0x59]，参考结构体UUVMOTORINDEX
	UUV_S16		motorspeed;			///< 电机转速，0x50,0x51,0x52,0x53垂直方向的转速取值范围为[-2800-2800]，0x58,0x59垂直方向的电机转速取值范围为[-1600-1600]
} UUVMOTOR_T, *PUUVMOTOR_T;


/** 外挂设备供电信息结构体 */ 
typedef struct tagUUVEXTERNALPOWER
{
	UUV_U8 POEpoweron;				///< POE设备    0表示开启，1表示关闭 
	UUV_U8 CANpoweron;				///< 外挂CAN设备 0表示开启，1表示关闭
} UUVEXTERNALPOWER_T, *PUUVEXTERNALPOWER_T;


/** 摄像机图像叠加osd开关结构体 */ 
typedef struct tagUUVOSD
{
	UUV_U8 osd_on;					///< osd总开关    0表示关闭，1表示开启
	UUV_U8 battery_on;				///< 电池显示  0表示关闭，1表示开启
} UUVOSD_T, *PUUVOSD_T;


/** 本体电源信息结构体 */ 
typedef struct
{
	UUV_U16 Voltage_IN;				///< 输入电压，[2000-5000]，单位0.1V
	UUV_U16 Current_IN;				///< 输入电流，[0-3000]，单位0.01A	
	UUV_U16 Voltage_BATT;			///< 电池电压，[1000-3000]，单位0.01V
	UUV_U16 Current_OUT;			///< 输出到负载的电流，[0-3000]，单位0.01A符号数，24v系统极限2000w
	UUV_U16 SOC;					///< 电池soc状态，[0-100]
	UUV_U16 stats;					///< 系统电源状态
	UUV_U16 Power_SYS;				///< 系统总功率，[0-8000]，单位w
	UUV_U16 reserved;				///< 预留
}POWER;								///< 电源系统状态


/** 本体云台和照明信息结构体 */ 
typedef struct
{
	UUV_S16 elevation;				///< 云台俯仰 [-380-380],单位0.1度，俯视为正
	UUV_S16 rotate;					///< 云台旋转 [-580-580],单位0.1度，右转为正
	UUV_S16 focus;					///< 相机聚焦 [0-100],梯度为1
	UUV_S16 zoom;					///< 相机变焦 [0-100],梯度为1
	UUV_U8 focus_mode;				///< 0 增量形式，[0-100]表示聚焦变焦的速度，1 绝对位置 [0-100]表示聚焦变焦到某个梯度
	UUV_S8 leftlight_lum;			///< 左灯亮度值 [0-100]
	UUV_S8 rightlight_lum;			///< 右灯亮度值，[0-100]
	UUV_U8 laser;					///< 预留
}CAM;


/** 电机转速结构体 */ 
typedef struct
{
	UUV_S16 l_f_v_motor;			///< 垂直左前电机转速 [-2800,2800]
	UUV_S16 l_b_v_motor;			///< 垂直左后电机转速 [-2800,2800]
	UUV_S16 r_f_v_motor;			///< 垂直右前电机转速 [-2800,2800]
	UUV_S16 r_b_v_motor;			///< 垂直右后电机转速 [-2800,2800]
	UUV_S16 l_h_motor;				///< 水平左电机转速 [-1600,1600]
	UUV_S16 r_h_motor;				///< 水平右电机转速 [-1600,1600]
	
}MOTOR;


/** 本体机械手信息结构体 */ 
typedef struct
{
	UUV_S8 switching;				///< 机械手开合状态 Bit0 =1：正在张开；Bit1 =1：正在闭合；Bit2 =1：达到最大张开位置；Bit3 = 1：达到最大闭合位置；
									///< Bit4 = 1：闭合过流，停止张开；Bit5 = 1：张开过流，停止闭合
									
	UUV_U8 rotate;					///< 单自由度机械手 此项保留
	UUV_U8 Telescopic;				///< 单自由度机械手 此项保留
	UUV_U8 reserved[5];				///< 单自由度机械手 此项保留
}Extraman;

					

/** 运动和姿态信息结构体 */ 
typedef struct						
{
	UUV_S16 roll;					///< 横滚角，[-900-900],单位为0.1度   右横滚为正
	UUV_S16 pitch;   				///< 俯仰角，[-900-900],单位为0.1度   俯视为正
	UUV_S16 yaw;					///< 航向角，[-1800-1800],单位为0.1度
	
	UUV_S16 forwar_backwar;			///< 前后速度，百分比形式 [-100-100]
	UUV_S16 left_right;				///< 横移速度，百分比形式 [-100-100]
	UUV_S16 up_down;				///< 上下速度，百分比形式 [-100-100]
	
	UUV_U8 operat_mode;				///< 工作模式，0-停转，1-自由，2-定深 0xff为调试模式  只有在调试模式下，才能直接对电机进行操作
	UUV_U8 yewmode;					///< bit0 航向控制方式，0差速，1姿态   bit1 导航控制模式  0惯导 1磁导
	UUV_S16 depth_aim;				///< 目标深度[0-10000],单位为0.01米
	UUV_U8 Att_Calibration;			///< 姿态校准  深度校准
	UUV_U8 reserved[3];				///< 预留
}Attitude;


/** UUV本体信息结构体 */ 
typedef struct						///< UUV本体状态信息结构体	
{
	Attitude ATT;					///< 姿态信息结构体 
	UUV_U16 power;					///< 板载设备供电状态	0开启，1关闭 bit0:摄像头，bit1:POE,bit2:外挂CAN总线
	
	UUV_S16 Temperature;			///< 舱外水温
	UUV_U16 Salinity;				///< 盐度，来自电导率传感器，百分比
	UUV_S16 depth;					///< 当前深度[0-10000],单位为0.01米
	UUV_S16 Temperature_in;			///< 机内温度
	UUV_U16 pressure_in;			///< 机内压力 kPa
	UUV_U16 humidity_in;			///< 机内湿度，百分比
	CAM camdata;					///< 摄像头信息 参照结构体CAM
	MOTOR motor;					///< 六个电机的转速信息 参照结构体MOTOR
	UUV_S16 llumination[2];			///< 保留
	Extraman extraman;				///< 机械手信息 参照结构体Extraman
	POWER p_inf;					///< 电源信息	参照结构体POWER
}UUV_STAT,*PUUV_STAT;


#endif // UUV_Command_Param_h__