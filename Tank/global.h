#ifndef __GLOBAL_H__
#define __GLOBAL_H__

namespace hwj 
{
	// ���ھ��
	typedef void * WINDOWHANDLE;

	// ��ʱ��
	typedef void * TIMER;

	// ������ʱ��
	bool CreateTimer(TIMER &timer);
	void WaitTimer(TIMER &timer, int milliSecond);
	void DestroyTimer(TIMER &timer);
}

#endif // __GLOBAL_H__
