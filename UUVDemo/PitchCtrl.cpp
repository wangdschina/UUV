#include "stdafx.h"
#include "PitchCtrl.h"


/** 
*  @brief             PID算法 
*  @param[in]         差值 
*  @param[in,out]     pid结构体
*  @return            pid计算结果
*  @remarks      
*  @see          
*/  
float PIDCalc(float Error, struct PID *PID_x)
{
	float dError;
	float d_out, out;
	float temp;

	dError = Error - PID_x->LastError;               // diretative

	d_out = PID_x->P * dError                                           //P
		+ PID_x->I * Error                                            //I
		+ PID_x->D * (Error - 2 * PID_x->LastError + PID_x->PrevError); //D

	out = d_out + PID_x->Last_u;
	PID_x->PrevError = PID_x->LastError;
	PID_x->LastError = Error;
	PID_x->Last_u = out;
	temp = out;
	return temp;
}


/** 定义给本体发数据的结构体 */ 
Result result = { 0 };


/** 
*  @brief       融合pid计算的结果 
*  @param[in]   fx：前进后退速度   
*  @param[in]   depth：pid计算的深度
*  @param[in]   roll：pid计算的横滚
*  @param[in]   pitch：pid计算的俯仰
*  @param[in]   yaw：pid计算的航向角
*  @return      无
*  @remarks      
*  @see          
*/  
void ControlTask(float fx, float depth, float roll, float pitch, float yaw)
{
	result.vLeftFront =  depth - roll - pitch;
	result.vLeftBack =  depth - roll + pitch;
	result.vRightBack =  depth + roll + pitch;
	result.vRightFront =  depth + roll - pitch;

	result.hLeft = fx + yaw;
	result.hRight = fx - yaw;
}


/** 
*  @brief       给电机发送数据 
*  @param[in]   index：电机的索引值 
*  @param[in]   speed：速度值
*  @return      无
*  @remarks      
*  @see          
*/  
void SendMotorSpeed( UUVMOTORINDEX index, int speed )
{
	unsigned char move_pattrn = 0xff;
	if(!m_pUUV->UUV_Set(UUV_WORK_PATTERN_SET, &move_pattrn))
	{
		printf("设置调试模式失败，错误码 %d", m_pUUV->UUV_GetErrno());
		return;
	}

	UUVMOTOR_T motor;
	motor.motorindex = index;
	motor.motorspeed = speed;
	if(!m_pUUV->UUV_Set(UUV_MOTOR_SPEED_SET, &motor))
	{
		printf("设置电机%x错误，错误码 %d", motor.motorindex, m_pUUV->UUV_GetErrno());
	}
}


/** 定义深度、横滚、俯仰、航向的pid结构体 */ 
struct PID pid_depth, pid_roll, pid_pitch, pid_yaw;


/** 定义用户输入的目标结构体 */ 
Target target = { 0 };


/** 
*  @brief       用户输入目标值测试函数
*  @return      无
*  @remarks      
*  @see          
*/ 
void PitchCtrlTest()
{
	printf("请输入你的目标值，格式为（速度、横滚、俯仰、深度、航向）\n");
	scanf("%f%f%f%f%f", &target.speed, &target.roll, &target.pitch, &target.depth, &target.yaw);
	printf("目标值为：%f, %f, %f, %f, %f\n", target.speed, target.roll, target.pitch, target.depth, target.yaw);

	pid_depth.P = 1000;
	pid_depth.I = 4;
	pid_roll.P = 35;
	pid_roll.I = 0.25;
	pid_roll.D = 0.2;
	pid_pitch.P = 40;
	pid_pitch.I = 0.3;
	pid_pitch.D = 0.2;
	pid_yaw.P = 20;
	pid_yaw.I = 0.4;
	pid_yaw.D = 0.1;
	//	PID算法
	printf("PID 计算中...\n");
	while(true)
	{
		float tmpRoll = PIDCalc(target.roll - puuv_status->ATT.roll*0.1, &pid_roll);
		float tmpPitch = PIDCalc(target.pitch - puuv_status->ATT.pitch*0.1, &pid_pitch);
		float tmpDepth = PIDCalc(target.depth - puuv_status->depth*0.01, &pid_depth);
		float tmpYaw = PIDCalc(target.yaw - puuv_status->ATT.yaw*0.1, &pid_yaw);

		ControlTask(target.speed, tmpDepth, tmpRoll, tmpPitch, tmpYaw);

		//	打印输出
		printf("\n左前：%d", result.vLeftFront);
		printf("\t左后：%d", result.vLeftBack);
		printf("\t右后：%d", result.vRightBack);
		printf("\t右前：%d", result.vRightFront);
		printf("\t水平左：%d", result.hLeft);
		printf("\t水平右：%d", result.hRight);

		//	发送数据
		SendMotorSpeed(V_L_F_MOTORINDEX, result.vLeftFront);
		SendMotorSpeed(V_L_B_MOTORINDEX, result.vLeftBack);
		SendMotorSpeed(V_R_B_MOTORINDEX, result.vRightBack);
		SendMotorSpeed(V_R_F_MOTORINDEX, result.vRightFront);
		SendMotorSpeed(H_L_MOTORINDEX, result.hLeft);
		SendMotorSpeed(H_R_MOTORINDEX, result.hRight);
	}
}
