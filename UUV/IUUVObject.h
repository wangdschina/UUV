/** 
*  Copyright (c) 2017, 天津深之蓝海洋设备科技有限公司(http://www.deepinfar.com/) 
*  All rights reserved. 
* 
*  @file        IUUVObject.h 
*  @author      wangds
*  @email		dengsheng.wang@deepinfar.com
*  @date        2017/05/11 17:09 
* 
*  @brief       UUV接口类 
*  @note        字符集均使用 Unicode 字符集  
* 
*  @version 
*    - v1.0   
*/  


#ifndef IUUVObject_h__
#define IUUVObject_h__

#ifdef UUV_EXPORTS
#define UUV_API __declspec(dllexport)
#else
#define UUV_API __declspec(dllimport)
#endif

class IUUVObject;

/** 
*  @brief       定义UUV本体状态的回调函数    
*  @param[out]  pResult：返回的结果 
*  @return      成功返回true，否则为false                 
*/  
typedef void (CALLBACK* UUVHandler)(UUV_RESULT pResult);

/** 
*  @brief       定义UUV摄像头返回数据的回调函数  
*  @param[out]  pFrameYUV：返回的YUV420数据
*  @return      成功返回true，否则为false                 
*/  
typedef void (CALLBACK* UUVVideoFrame)(UUV_RESULT pFrameYUV);

/** 
*  @brief       定义USBL返回数据的回调函数  
*  @param[out]  pusbl：返回的USBL相关数据
*  @return      成功返回true，否则为false                 
*/  
typedef void (CALLBACK* UUVUSBLData)(UUV_RESULT pusbl);

/** 
*  @brief       创建一个UUV的实例，调用接口之前先调用此函数 
*  @param[in]   type： E_UUV_TYPE中定义的类型
*  @return      返回type类型的IUUVObject对象，无type类型返回NULL    
*/  
UUV_API IUUVObject* CreateUUV(E_UUV_TYPE type);


/** 
*  @brief       释放由CreateUUV创建的UUV实例 
*  @param[in]   pUUV：由CreateUUV创建的IUUVObject对象 
*  @return      无
*/  
UUV_API void ReleaseUUV(IUUVObject* pUUV);


/** 
*  @author      wangds
*  @email		dengsheng.wang@deepinfar.com
*  @date        2017/05/11 17:12 
*  @class       IUUVObject 
*  @brief       定义UUV可调用的接口 
*  @note        无 
*/  
class UUV_API IUUVObject
{
public:
	virtual ~IUUVObject(){}

	/** 
	*  @brief       注册UUV本体返回状态的回调函数 
	*  @param[in]   pHandler：本体状态的回调函数
	*  @return      成功返回true，否则为false
	*/  
	virtual bool UUV_RegHandler(UUVHandler pHandler) = 0;

	/** 
	*  @brief       注册UUV摄像头返回数据的回调函数 
	*  @param[in]   pVideoHandler：摄像头返回的YUV数据
	*  @return      成功返回true，否则为false          
	*/  
	virtual bool UUV_RegVideoHandler(UUVVideoFrame pVideoHandler) = 0;

	/** 
	*  @brief       注册USBL返回数据的回调函数 
	*  @param[in]   pUSBLHandler：USBL数据的回调函数
	*  @return      成功返回true，否则为false          
	*/  
	virtual bool UUV_RegUSBLHandler(UUVUSBLData pUSBLHandler) = 0;



	/** 
	*  @brief       UUV获取数据的接口 
	*  @param[in]   strCommand：UUV_COMMAND中定义的<get>命令  
	*  @param[out]  pResult：查询命令获取的结果 
	*  @return      成功返回true，否则为false                 
	*/  
	virtual bool UUV_Get(UUV_COMMAND strCommand, UUV_RESULT& pResult) = 0;

	/** 
	*  @brief       UUV设置数据的接口 
	*  @param[in]   strCommand：UUV_COMMAND中定义的<set>命令 
	*  @param[in]   param：对应的参数
	*  @return      成功返回true，否则为false                 
	*/  
	virtual bool UUV_Set(UUV_COMMAND strCommand, UUV_PARAM	param) = 0;

public:
	/** 
	*  @brief       UUV返回最后一次错误码 
	*  @return      返回int错误码                
	*/  
	virtual int UUV_GetErrno(void) = 0;
};


#endif // IUUVObject_h__

