/** 
*  Copyright (c) 2017, 天津深之蓝海洋设备科技有限公司(http://www.deepinfar.com/) 
*  All rights reserved. 
* 
*  @file        UUV_Command.h 
*  @author      wangds
*  @email		dengsheng.wang@deepinfar.com
*  @date        2017/05/11 16:57 
* 
*  @brief       UUV命令 
*  @note        无 
* 
*  @version 
*    - v1.0     
*/  

#ifndef UUV_Command_h__
#define UUV_Command_h__

/** UUV命令定义 */ 
enum UUV_COMMAND
{
	UUV_NET_OPEN = 1,						///<	<set>打开网络
	UUV_NET_CLOSE,							///<	<set>关闭网络
	UUV_NET_STATE,							///<	<get>获取网络状态
	UUV_SYSTEM_POWER_SET,					///<	<set>系统软重启  参数固定为1							参数类型 UUV_U8

	/** UUV工作模式、控制方式和功耗等参数设置 */ 
	UUV_WORK_PATTERN_SET = 100,				///<	<set>工作方式   0停止，1自由 2 定深	0xff 为调试模式 启动调试模式，可独立控制各个电机转动		参数类型 UUV_U8
	UUV_YAW_NAVIGATES_SET,					///<	<set>导航模式  0惯导，1磁导								参数类型 UUV_U8
	UUV_YAW_CONTROL_SET,					///<	<set>航向控制方式 0差速，1姿态							参数类型 UUV_U8
	UUV_CONSUMPTION_SET,					///<	<set>功耗模式设置  0 高功耗 1 低功耗 默认为低功耗		参数类型 UUV_U8

	/** UUV外挂设备供电设置 */ 
	UUV_CAMERA_POWER_SET = 200,				///<	<set>摄像机供电
	UUV_POE_CAN_POWER_SET,					///<	<set>POE（声呐供电）、CAN（机械手）供电					参数类型 UUVEXTERNALPOWER_T

	/** UUV姿态和运动参数设置 */ 
	UUV_ATT_ROLL_SET = 300,					///<	<set>横滚设置 [-450-450]，单位为0.1度					参数类型 UUV_S16
	UUV_ATT_PITCH_SET,						///<	<set>俯仰设置 [-450-450]，单位为0.1度					参数类型 UUV_S16
	UUV_ATT_YAW_SET,						///<	<set>在姿态控制模式下 [-1800-1800],单位为0.1度，差速控制模式下 [-100-100]  参数类型 UUV_S16
	UUV_FORWARD_BACKWARD_SPEED_SET,			///<	<set>前后速度设置 百分比形式 [-100-100]					参数类型 UUV_S16
	UUV_LEFT_RIGHT_SPEED_SET,				///<	<set>横移速度设置 百分比形式 [-100-100]					参数类型 UUV_S16
	UUV_TARGET_DEPTH_SET,					///<	<set>目标深度 [0-10000],单位为cm						参数类型 UUV_S16
	
	/** UUV外挂设备参数设置 */ 
	UUV_CAMERA_ZOOM_SET = 400,				///<	<set>摄像头变焦	  百分比形式 [0-100]					参数类型 UUV_U8
	UUV_CAMERA_FOUCUS_SET,					///<	<set>摄像头聚焦	  百分比形式 [0-100]					参数类型 UUV_U8
	UUV_CAMERA_PITCH_SET,					///<	<set>云台俯仰	  百分比形式 [-100-100]					参数类型 UUV_S16
	UUV_CAMERA_ROTATE_SET,					///<	<set>云台旋转	  百分比形式 [-100-100]					参数类型 UUV_S16
	UUV_LIGHT_VALNE_SET,					///<	<set>灯光设置  设置灯光亮度								参数类型 UUVLIGHT_T
	UUV_CAMERA_OSD_SET,						///<	<set>设置视频上叠加的图标								参数类型 UUVOSD_T
	UUV_MANIP_OPERATION_SET,				///<	<set> 机械手开合速度  [-100-100]	100 最大速度张开  -100最大速度闭合 参数类型 UUV_S16
	
	/** UUV电机转速参数设置，用于客户姿态算法调试 */ 
	UUV_MOTOR_SPEED_SET = 500,				///<	<set>电机速度设定 只有在调试模式下该设置有效			参数类型 UUVMOTOR_T

};
#endif // UUV_Command_h__