#ifndef __GLOBAL_H__
#define __GLOBAL_H__

namespace hwj 
{
	// 窗口句柄
	typedef void * WINDOWHANDLE;

	// 定时器
	typedef void * TIMER;

	// 创建定时器
	bool CreateTimer(TIMER &timer);
	void WaitTimer(TIMER &timer, int milliSecond);
	void DestroyTimer(TIMER &timer);
}

#endif // __GLOBAL_H__
