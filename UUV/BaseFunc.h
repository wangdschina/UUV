/** 
*  Copyright (c) 2017, 天津深之蓝海洋设备科技有限公司(http://www.deepinfar.com/) 
*  All rights reserved. 
* 
*  @file        BaseFunc.h 
*  @author      wangds
*  @email		dengsheng.wang@deepinfar.com
*  @date        2017/05/15 09:27 
* 
*  @brief       通用函数 
* 
*  @version 
*    - v1.0   
*/  

#ifndef BaseFunc_h__
#define BaseFunc_h__

#include "PacketizedTcp.h"
#include "PacketizedUdp.h"

/** 打印日志类型 */ 
enum WT_EVENTLOG_TYPE
{
	WT_EVENTLOG_SUCCESS_TYPE = 0x0000,		///< 成功
	WT_EVENTLOG_ERROR_TYPE = 0x0001,		///< 错误
	WT_EVENTLOG_WARNING_TYPE = 0x0002,		///< 警告
	WT_EVENTLOG_INFORMATION_TYPE = 0x0004  ///< 消息
};

/** 
*  @brief       日志回调函数，如果想要在自己的窗体中显示日志，请用函数指针g_logCallBack说明要回调的函数 
*  @param[in]   emType：日志类型 
*  @param[in]   stTime：系统时间
*  @param[in]   lpszMsg：日志消息
*  @return      无返回值              
*/  
typedef void (CALLBACK* LogCallBack)(WT_EVENTLOG_TYPE emType, SYSTEMTIME stTime, LPCTSTR lpszMsg);

/** 日志存放路径的载入模块，默认为NULL，存放路径为程序运行目录的Log目录中 */ 
extern HMODULE g_hModule;

/** 日志回调函数指针 */ 
UUV_API extern LogCallBack g_logCallBack;

/** 
*  @brief       打印日志，默认路径存放在用户目录下的Log目录中 
*  @param[in]   emType：打印日志类型， 使用WT_EVENTLOG_TYPE说明
*  @param[in]   lpszFmt：打印日志格式
*  @return      无返回值                
*/  
UUV_API void LogMsg(WT_EVENTLOG_TYPE emType, LPCTSTR lpszFmt, ...);


/** 
*  @brief       创建TCP客户端接口   
*  @return      返回客户端接口指针
*/  
IPacketizedTcpClient* CreatePacketizedTcpClient();


/** 
*  @brief       返回UDP客户端接口  
*  @return      返回客户端接口指针           
*/  
IPacketizedUdpClient* CreatePacketizedUdpClient();


/** 
*  @brief       CRC16校验 
*  @param[in]   puchMsg：校验数据 
*  @param[in]   crc_count：校验数据长度
*  @return      返回校验值
*/  
unsigned short Crc16_Check(unsigned char *puchMsg,unsigned char crc_count);

#endif // BaseFunc_h__