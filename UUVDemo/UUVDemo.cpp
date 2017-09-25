/** 
*  Copyright (c) 2017, 天津深之蓝海洋设备科技有限公司(http://www.deepinfar.com/) 
*  All rights reserved. 
* 
*  @file        Sample.cpp 
*  @author      wangds
*  @email		dengsheng.wang@deepinfar.com
*  @date        2017/05/16 16:17 
* 
*  @brief       使用Sublue UUV SDK简单的demo 
*  @note        字符集均使用 Unicode 字符集 
* 
*  @version 
*    - v1.0   
*/ 

#include "stdafx.h"
#include "PitchCtrl.h"

/** 定义UUV对象，创建时调用CreateUUV函数，销毁时调用ReleaseUUV */ 
IUUVObject* m_pUUV = nullptr;


/** 定义前进后退速度 */ 
short nSpeed = 0;


/** 定义俯仰角度 */ 
short nPitch = 0;


/** 定义横滚角度 */ 
short nRoll = 0;


/** 定义UUV状态对象 */ 
PUUV_STAT puuv_status = nullptr;


/** 定义USBL数据对象指针 */ 
PUUV_USBL_INFO pusbl_data = nullptr;


/** 定义是否开启人脸识别 */ 
bool open_face_detect = false;


/** 
*  @brief		UUV本体数据回调函数 
*  @param[out]  pResult：UUV本体返回的数据  
*  @return		无            
*/  
static void CALLBACK UUVResultShow(UUV_RESULT pResult);


/** 
*  @brief		打印UUV本体数据 
*  @param[out]  无
*  @return		无            
*/  
void ShowUUVData(void);


/** 
*  @brief       摄像头数据回调函数 
*  @param[out]  pResult：摄像头返回的yuv420数据  
*  @return      无          
*/  
static void CALLBACK UUVVideoFrameCallBack(UUV_RESULT pResult);


/** 
*  @brief		打印USBL数据 
*  @param[out]  无
*  @return		无            
*/  
void ShowUSBLData(void);


/** 
*  @brief       USBL数据回调函数 
*  @param[out]  pResult：USBL返回的数据  
*  @return      无          
*/  
static void CALLBACK UUVUSBLDataCallBack(UUV_RESULT pResult);


/** 
*  @brief       初始化UUV对象 
*  @param[in]   无 
*  @return      
*/  
bool InitUUV()
{
	m_pUUV = CreateUUV(E_ROV_SHARK_MAX);
	if (m_pUUV == nullptr)
	{
		printf("创建UUV实例失败\n");
		exit(1);
	}
	else
	{
		if (!m_pUUV->UUV_RegHandler(UUVResultShow))
		{
			printf("注册UUV本体数据回调失败，错误码%d\n", m_pUUV->UUV_GetErrno());
		}
		if (!m_pUUV->UUV_RegUSBLHandler(UUVUSBLDataCallBack))
		{
			printf("注册UUV USBL数据回调失败，错误码%d\n", m_pUUV->UUV_GetErrno());
		}
		if (!m_pUUV->UUV_RegVideoHandler(UUVVideoFrameCallBack))
		{
			printf("注册UUV视频数据回调失败，错误码%d\n", m_pUUV->UUV_GetErrno());
		}
	}
}


/** 
*  @brief       打开连接 
*  @param[in]   无   
*  @return      
*  @remarks     该框架中已经附有重连机制 
*/  
void NetOpen()
{
	UUVNETOPEN netOpen;
	netOpen.strIP = _T("192.168.99.10");
	netOpen.nPort = 5001;
	netOpen.hWnd = NULL;
	if(!m_pUUV->UUV_Set(UUV_NET_OPEN, &netOpen))
	{
		printf("打开连接失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}

	if (!m_pUUV->UUV_Set(UUV_USBL_NET_OPEN, NULL))
	{
		printf("打开USBL连接失败，错误码%d\n", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       关闭连接 
*  @param[in]   无  
*  @return                  
*/  
void NetClose()
{
	if(!m_pUUV->UUV_Set(UUV_NET_CLOSE, nullptr))
	{
		printf("关闭连接失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}

	if(!m_pUUV->UUV_Set(UUV_USBL_NET_CLOSE, nullptr))
	{
		printf("关闭USBL连接失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       获取连接状态 
*  @param[in]   无   
*  @return      
*/  
void NetState()
{
	UUV_RESULT pResult = new UUV_RESULT;
	if(!m_pUUV->UUV_Get(UUV_NET_STATE, pResult))
	{
		printf("获取网络连接状态失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}
	else
	{
		E_NET_STATE* netState = (E_NET_STATE*)(pResult);
		if (!netState)
		{
			printf("类型转换失败\n");
		}
		else
		{
			tstring strState = _T("连接状态未知");
			switch (*netState)
			{
			case E_NET_CONNING:
				printf("网络状态：正在连接\n");
				break;
			case E_NET_CONNED:
				printf("网络状态：已连接\n");
				break;
			case E_NET_DISCONNING:
				printf("网络状态：正在断开\n");
				break;
			case E_NET_DISCONNED:
				printf("网络状态：已断开\n");
				break;
			default:
				break;
			}
		}
	}

	if (!pResult)
	{
		delete pResult;
		pResult = nullptr;
	}
}


/** 
*  @brief       前进
*  @param[in]   无  
*  @return          
*  @remarks     步进速度每次+1，速度最大为100
*/ 
void Forward(void)
{
	unsigned char move_pattrn = 2;
	if(!m_pUUV->UUV_Set(UUV_WORK_PATTERN_SET, &move_pattrn))
	{
		printf("设置定深模式失败，错误码 %d", m_pUUV->UUV_GetErrno());
		return;
	}

	if (nSpeed++ > 100)
	{
		nSpeed = 100;
		printf("前进速度已达最大值\n");
	}

	if(!m_pUUV->UUV_Set(UUV_FORWARD_BACKWARD_SPEED_SET, &nSpeed))
	{
		printf("设置前进速度失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       后退
*  @param[in]   无  
*  @return          
*  @remarks     步进速度每次-1，速度最小为-100
*/ 
void Back(void)
{
	unsigned char move_pattrn = 2;
	if(!m_pUUV->UUV_Set(UUV_WORK_PATTERN_SET, &move_pattrn))
	{
		printf("设置定深模式失败，错误码 %d", m_pUUV->UUV_GetErrno());
		return;
	}

	if (nSpeed-- < -100)
	{
		nSpeed = -100;
		printf("后退速度已达最大值\n");
	}

	if(!m_pUUV->UUV_Set(UUV_FORWARD_BACKWARD_SPEED_SET, &nSpeed))
	{
		printf("设置后退速度失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       仰视
*  @param[in]   无  
*  @return          
*  @remarks     步进角度每次1，角度最小为450（即45°）
*/ 
void Up(void)
{
	unsigned char move_pattrn = 2;
	if(!m_pUUV->UUV_Set(UUV_WORK_PATTERN_SET, &move_pattrn))
	{
		printf("设置定深模式失败，错误码 %d", m_pUUV->UUV_GetErrno());
		return;
	}

	if (nPitch++ > 450)
	{
		nPitch = 450;
		printf("仰视角已达最大值\n");
	}
	
	//short nSpeed = puuv_status->ATT.pitch - 1;
	if(!m_pUUV->UUV_Set(UUV_ATT_PITCH_SET, &nPitch))
	{
		printf("设置仰视失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       俯视
*  @param[in]   无  
*  @return          
*  @remarks     步进角度每次-1，角度最大为-450（即-45°）
*/ 
void Down(void)
{
	unsigned char move_pattrn = 2;
	if(!m_pUUV->UUV_Set(UUV_WORK_PATTERN_SET, &move_pattrn))
	{
		printf("设置定深模式失败，错误码 %d", m_pUUV->UUV_GetErrno());
		return;
	}

	if (nPitch-- < -450)
	{
		nPitch = -450;
		printf("俯视角已达最大值\n");
	}
	
	//short nSpeed = puuv_status->ATT.pitch + 1;
	if(!m_pUUV->UUV_Set(UUV_ATT_PITCH_SET, &nPitch))
	{
		printf("设置俯视失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       左横滚
*  @param[in]   无  
*  @return          
*  @remarks     步进角度每次-1，角度最小为-450（即-45°）
*/ 
void Left(void)
{
	unsigned char move_pattrn = 2;
	if(!m_pUUV->UUV_Set(UUV_WORK_PATTERN_SET, &move_pattrn))
	{
		printf("设置定深模式失败，错误码 %d", m_pUUV->UUV_GetErrno());
		return;
	}

	if (nRoll-- < -450)
	{
		nRoll = -450;
		printf("左横滚角已达最大值\n");
	}
	
	//short nSpeed = puuv_status->ATT.roll - 1;
	if(!m_pUUV->UUV_Set(UUV_ATT_ROLL_SET, &nRoll))
	{
		printf("设置左横滚失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       右横滚
*  @param[in]   无  
*  @return          
*  @remarks     步进角度每次+1，角度最大为450（即45°）
*/ 
void Right(void)
{
	unsigned char move_pattrn = 2;
	if(!m_pUUV->UUV_Set(UUV_WORK_PATTERN_SET, &move_pattrn))
	{
		printf("设置定深模式失败，错误码 %d", m_pUUV->UUV_GetErrno());
		return;
	}

	if (nRoll++ > 450)
	{
		nRoll = 450;
		printf("右横滚角已达最大值\n");
	}
	
	//short nSpeed = puuv_status->ATT.roll + 1;
	if(!m_pUUV->UUV_Set(UUV_ATT_ROLL_SET, &nRoll))
	{
		printf("设置右横滚失败，错误码 %d\n", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       灯光设置，设置左灯
*  @return      无
*  @remarks     步进值每次+1，最大为100（右灯最小为-100）       
*/  
void LeftLight(void)
{
	UUVLIGHT_T light;
	light.lightindex = 0;	//	0-代表左灯，1-代表右灯
	light.lum = 100;
	if(!m_pUUV->UUV_Set(UUV_LIGHT_VALNE_SET, &light))
	{
		printf("设置左灯亮度失败，错误码 %d", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       OSD设置
*  @return      无
*  @remarks     0-不显示，1-显示
*/  
void OSD(void)
{
	UUVOSD_T osd;
	osd.osd_on = 1;	
	osd.battery_on = 1;
	if(!m_pUUV->UUV_Set(UUV_CAMERA_OSD_SET, &osd))
	{
		printf("设置图像OSD度失败，错误码 %d", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       机械手设置
*  @return      无
*  @remarks     0：停止状态，-100：以最大速度闭合，100：以最大速度张开
*/  
void ManipControl(void)
{
	int tmp = 100;
	if(!m_pUUV->UUV_Set(UUV_MANIP_OPERATION_SET, &tmp))
	{
		printf("设置机械手操作失败，错误码 %d", m_pUUV->UUV_GetErrno());
	}
}


/** 
*  @brief       用户帮助快捷键
*  @param[in]   无  
*  @return          
*  @remarks     不在列表当中的没做处理，用户可以自定义添加
*/ 
void Help(void)
{
	char* info = "\n这是一个简单使用UUV的样例\n"
		"\t Hot keys: \n"
		"\t	h	- help \n"
		"\t	q	- 退出程序\n"
		"\t	o	- 打开连接\n"
		"\t	c	- 关闭连接\n"
		"\t	s	- 获取网络状态\n"
		"\t	f	- 前进（网络连接后才可进行此操作）\n"
		"\t	b	- 后退（网络连接后才可进行此操作）\n"
		"\t	u	- 仰视（网络连接后才可进行此操作）\n"
		"\t	d	- 俯视（网络连接后才可进行此操作）\n"
		"\t	l	- 左横滚（网络连接后才可进行此操作）\n"
		"\t	r	- 右横滚（网络连接后才可进行此操作）\n"
		"\t	p	- 打印本体数据\n"
		"\t a   - 打印USBL数据\n"
		"\t	t	- 目标识别\n"
		"\t	*	- 按任意键开始目标输入\n";

	printf("%s", info);
}


/** 
*  @brief       程序入口处 
*  @param[in]    
*  @param[in]   
*  @return      exit code
*/  
int main(int argc, char* argv[])
{
	Help();
	if (InitUUV())
	{
		while (true)
		{
			char c = (char)getch();
			switch (c)
			{
			case 'h':
				{
					Help();
				}
				break;
			case 'o':
				{
					NetOpen();
				}
				break;
			case 'c':
				{
					NetClose();
				}
				break;
			case 's':
				{
					NetState();
				}
				break;
			case 'f':
				{
					Forward();
				}
				break;
			case 'b':
				{
					Back();
				}
				break;
			case 'u':
				{
					Up();
				}
				break;
			case 'd':
				{
					Down();
				}
				break;
			case 'l':
				{
					Left();
				}
				break;
			case 'r':
				{
					Right();
				}
				break;
			case 't':
				{
					open_face_detect = true;
				}
				break;
			case 'p':
				{
					ShowUUVData();
				}
				break;
			case 'a':
				{
					ShowUSBLData();
				}
				break;
			case 'q':
				{
					NetClose();
					ReleaseUUV(m_pUUV);
				}
				exit(0);
			default:
				{
					PitchCtrlTest();
				}
				break;
			}
		}
	}

	return 0;
}


/** 
*  @brief       UUV本体返回的数据 
*  @param[in]   pResult    
*  @return      无
*  @remarks		该回调只用来做显示      
*  @see          
*/  
void CALLBACK UUVResultShow( UUV_RESULT pResult )
{
	if (puuv_status == nullptr)
	{
		puuv_status = new UUV_STAT;
	}
	puuv_status = (PUUV_STAT)pResult;
}




/** 
*  @brief       显示UUV本体返回的数据
*  @param[in]   无    
*  @return      无
*  @remarks		      
*  @see          
*/  
void ShowUUVData(void)
{
	if (puuv_status == nullptr)
	{
		printf("未接收到UUV本体返回的数据，请检查网络是否已连接\n");
		return;
	}
	// Add your code about info of UUV
	printf("横滚角 = %0.1f\n", puuv_status->ATT.roll*0.1);
	printf("俯仰角 = %0.1f\n", puuv_status->ATT.pitch*0.1);
	printf("航向角 = %0.1f\n", puuv_status->ATT.yaw*0.1);
	printf("前后速度 = %d\n", puuv_status->ATT.forwar_backwar);
	printf("工作模式 = %d\n", puuv_status->ATT.operat_mode);
	printf("控制模式 = %d\n", puuv_status->ATT.yewmode&0x01);
	printf("导航模式 = %d\n", puuv_status->ATT.yewmode&0x02);
	printf("当前深度 = %0.2f\n", puuv_status->depth*0.01);
	printf("垂直左前电机转速 = %d\n", puuv_status->motor.l_f_v_motor);
	printf("垂直左后电机转速 = %d\n", puuv_status->motor.l_b_v_motor);
	printf("垂直右后电机转速 = %d\n", puuv_status->motor.r_b_v_motor);
	printf("垂直右前电机转速 = %d\n", puuv_status->motor.r_f_v_motor);
	printf("水平左电机转速 = %d\n", puuv_status->motor.l_h_motor);
	printf("水平右电机转速 = %d\n", puuv_status->motor.r_h_motor);
	//	未完，需要打印别的信息，在此添加
}


/** 
*  @brief       USBL返回的数据 
*  @param[in]   pResult    
*  @return      无
*  @remarks		该回调只用来做显示      
*  @see          
*/  
void CALLBACK UUVUSBLDataCallBack(UUV_RESULT pResult)
{
	if (pusbl_data == nullptr)
	{
		pusbl_data = new UUV_USBL_INFO;
	}
	pusbl_data = (PUUV_USBL_INFO)pResult;
}

/** 
*  @brief       显示UUV本体返回的数据
*  @param[in]   无    
*  @return      无
*  @remarks		      
*  @see          
*/  
void ShowUSBLData(void)
{
	if (pusbl_data == nullptr)
	{
		printf("未接收到USBL返回的数据，请检查网络是否已连接\n");
		return;
	}
	// Add your code about info of UUV
	printf("UUV位于基阵的距离 = %f米\n",pusbl_data->uuv_ralatived_distannce);
	printf("UUV位于基阵的角度 = %f度\n", pusbl_data->uuv_ralatived_direction);
	printf("UUV相对基阵偏北 = %f米\n", pusbl_data->uuv_ralatived_pos_north);
	printf("UUV相对基阵偏东 = %f米\n", pusbl_data->uuv_ralatived_pos_east);
	printf("UUV的经度 = %f度\n", pusbl_data->uuv_longitude);
	printf("UUV的纬度 = %f度\n", pusbl_data->uuv_latitude);

	//	未完，需要打印别的信息，在此添加
}



/** 
*  @brief       检测人脸并圈出 
*  @param[in]   img：要检测的图像 
*  @param[in]	cascade：人脸图像训练集
*  @param[in]	nestedCascade：人眼图像训练集
*  @param[in]	scale：图像缩放比例，加快检测速度
*  @param[in]	tryflip：是否使能，使能检测率高，但速度慢
*  @return      无         
*/  
void DetectAndDraw( cv::Mat& img, cv::CascadeClassifier& cascade, cv::CascadeClassifier& nestedCascade, double scale, bool tryflip )
{
	using namespace cv;

	//定义一些颜色，用来标示不同的人脸
	const static Scalar colors[] =  {
		CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255)} ;

	//建立缩小的图片，加快检测速度
	//nt cvRound (double value) 对一个double型的数进行四舍五入，并返回一个整型数！
	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );

	//转成灰度图像，Harr特征基于灰度图
	cvtColor( img, gray, CV_BGR2GRAY );
	//改变图像大小，使用双线性差值
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
	//变换后的图像进行直方图均值化处理
	equalizeHist( smallImg, smallImg );
	//程序开始和结束插入此函数获取时间，经过计算求得算法执行时间
	double t = (double)cvGetTickCount();

	//建立用于存放人脸的向量容器
	vector<cv::Rect> faces, faces2;

	//检测人脸
	//detectMultiScale函数中smallImg表示的是要检测的输入图像为smallImg
	//faces表示检测到的人脸目标序列
	//1.1表示每次图像尺寸减小的比例为1.1
	//2表示每一个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大小都可以检测到人脸)
	//CV_HAAR_SCALE_IMAGE表示不是缩放分类器来检测，而是缩放图像
	//Size(30, 30)为目标的最小最大尺寸
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		|CV_HAAR_SCALE_IMAGE
		,Size(30, 30));
	//如果使能，翻转图像继续检测
	if( tryflip )
	{
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale( smallImg, faces2,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			|CV_HAAR_SCALE_IMAGE
			,Size(30, 30) );
		for( vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); ++r )
		{
			faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
		}
	}
	t = (double)cvGetTickCount() - t;
	printf("detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.));
	int i = 0;
	vector<Rect>::const_iterator r = faces.begin();
	for( ; r != faces.end(); ++r, ++i )
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i%8];
		int radius;

		double aspect_ratio = (double)r->width/r->height;
		if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
		{
			//标示人脸时在缩小之前的图像上标示，所以这里根据缩放比例换算回去
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			circle( img, center, radius, color, 3, 8, 0 );
		}
		else
		{
			rectangle( img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
				cvPoint(cvRound((r->x + r->width-1)*scale), cvRound((r->y + r->height-1)*scale)),
				color, 3, 8, 0);
		}
		if( nestedCascade.empty() )
			continue;
		smallImgROI = smallImg(*r);
		//同样方法检测人眼
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			|CV_HAAR_SCALE_IMAGE
			,Size(30, 30) );
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); ++nr )
		{
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle( img, center, radius, color, 2, 8, 0 );
		}
	}

	/*	目标若存在，对第一目标做一个简单的跟踪，只用来做演示	*/
	if (r != faces.end())
	{
		Point faceCenter(cvRound(r->x + r->width*0.5), cvRound(r->y + r->height*0.5));	/*	目标中心点	*/
		Point smallCenter(smallImg.cols*0.5, smallImg.rows*0.5);	/*	原始图像中心点	*/
		if (faceCenter.x < smallCenter.x && faceCenter.y < smallCenter.y)	/*	目标在原始图像左上方	*/
		{
			Left();
			Up();
			Forward();
		}
		else if (faceCenter.x < smallCenter.x && faceCenter.y > smallCenter.y)	/*	目标在原始图像左下方	*/
		{
			Left();
			Down();
			Forward();
		}
		else if (faceCenter.x > smallCenter.x && faceCenter.y < smallCenter.y)	/*	目标在原始图像右上方	*/
		{
			Right();
			Up();
			Forward();
		}
		else if (faceCenter.x > smallCenter.x && faceCenter.y > smallCenter.y)	/*	目标在原始图像右下方	*/
		{
			Right();
			Down();
			Forward();
		}
		else    /*	目标在原始图像中心位置，不做处理	*/
		{

		}
	}

	if (!faces.empty())
	{
		imshow( "识别结果", img );
		waitKey(10000);
	}
}


/** 
*  @brief       摄像头数据回调函数 
*  @param[in]   pResult：yuv420数据帧    
*  @return      无
*  @remarks		该程序只用来做演示，不考虑效率等，请勿在回调中做耗时的任务
*/  
void CALLBACK UUVVideoFrameCallBack( UUV_RESULT pResult )
{
	AVFrame* pFrameYUV = static_cast<AVFrame*>(pResult);
	if (pFrameYUV == nullptr)
	{
		return;
	}

	if (open_face_detect)
	{
		open_face_detect = false;	/*	为了不丢图像帧，单次只识别一次；需要连续识别的话，一直按快捷键	*/

		using namespace cv;

		CascadeClassifier cascade, nestedCascade;
		cascade.load("data\\haarcascades\\haarcascade_frontalface_alt.xml");
		nestedCascade.load("data\\haarcascades\\haarcascade_eye.xml");

		Mat yuvImg;
		yuvImg.create(pFrameYUV->height*3/2, pFrameYUV->width, CV_8UC1);
		memcpy(yuvImg.data, pFrameYUV->data[0], (pFrameYUV->width)*(pFrameYUV->height));
		memcpy(yuvImg.data + (pFrameYUV->width)*(pFrameYUV->height), pFrameYUV->data[1], (pFrameYUV->width)*(pFrameYUV->height)/4);
		memcpy(yuvImg.data +(pFrameYUV->width)*(pFrameYUV->height) + (pFrameYUV->width)*(pFrameYUV->height)/4, pFrameYUV->data[2], (pFrameYUV->width)*(pFrameYUV->height)/4);

		Mat smallImg;
		resize(yuvImg, smallImg, Size(640, 480));
		Mat rgbImg;
		cvtColor(smallImg, rgbImg, CV_YUV2BGR_I420);

		DetectAndDraw(rgbImg, cascade, nestedCascade, 2, 0);
	}
}

