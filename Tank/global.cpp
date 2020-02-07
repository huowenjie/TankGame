#include "global.h"
#include <Windows.h>

namespace hwj
{
	bool CreateTimer(TIMER &timer) 
	{
		timer = CreateWaitableTimer(NULL, FALSE, NULL);
		return timer != NULL;
	}
	
	void WaitTimer(TIMER &timer, int milliSecond)
	{
		if (!timer || milliSecond <= 0) {
			return;
		}

		LARGE_INTEGER li = { 0 };
		li.QuadPart = -milliSecond * 10000;

		if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
			return;
		}

		WaitForSingleObject(timer, INFINITE);
	}
	
	void DestroyTimer(TIMER &timer) 
	{
		CloseHandle(timer);
	}
}
