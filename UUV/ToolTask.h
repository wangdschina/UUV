#pragma once

#include "Poco/Task.h"

using Poco::Task;


class CToolTask : public Task
{
public:
	CToolTask(const std::string& name);
	virtual ~CToolTask(void);
};

/*	解析任务	*/
class CParseTask : public CToolTask
{
public:
	CParseTask();
	~CParseTask();

	virtual void runTask();
	
protected:
	static int AVInterruptCallBackFun(void* ctx);

private:
	bool	m_bD3dInited;
	static int64_t	m_dwLastFrameRealTime; // 定义为静态变量，延迟生命周期；否则在程序退出后AVInterruptCallBackFun的生命周期未结束，导致调用被的函数失败而崩掉
};