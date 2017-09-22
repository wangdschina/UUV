/** 
*  Copyright (c) 2017, 天津深之蓝海洋设备科技有限公司(http://www.deepinfar.com/) 
*  All rights reserved. 
* 
*  @file        UUV_ErrCode.h 
*  @author      wangds
*  @email		dengsheng.wang@deepinfar.com
*  @date        2017/05/11 17:07 
* 
*  @brief       定义UUV错误码 
*  @note        无 
* 
*  @version 
*    - v1.0   
*/  


#ifndef UUV_ErrCode_h__
#define UUV_ErrCode_h__


const int ERR_SUCCESS				= 0;				///<	执行成功
const int ERR_BASE 					= 10000000;
const int ERR_NOTSUPPORTED 			= ERR_BASE + 1;		///<	不支持的命令
const int ERR_INVALIDPARAM			= ERR_BASE + 2;		///<	无效的参数
const int ERR_INVALIDHWND			= ERR_BASE + 3;		///<	无效的句柄
const int ERR_OUTOFRANGE			= ERR_BASE + 4;		///<	数据越界
const int ERR_OUTOFMEMORY			= ERR_BASE + 5;		///<	内存不足
const int ERR_EMPTYDATA				= ERR_BASE + 6;		///<	数据为空
const int ERR_TIMEOUT				= ERR_BASE + 7;		///<	超时
const int ERR_FILECREATEFAILED		= ERR_BASE + 8;		///<	文件创建失败
const int ERR_FILENOTEXIST			= ERR_BASE + 9;		///<	文件不存在
const int ERR_FILEALREADYEXIST		= ERR_BASE + 10;	///<	文件已存在
const int ERR_INVALIDPATH			= ERR_BASE + 11;	///<	路径无效

const int ERR_INNEREXCEPTION		= ERR_BASE + 999;	///<	内部异常


#endif // UUV_ErrCode_h__