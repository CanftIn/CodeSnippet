#include "Thread.h"

namespace CAN
{

	DWORD WINAPI ThreadOne(LPVOID lpParameter)
	{
		printf("ThreadOne is Runing\n");
		Sleep(100);
		return 0;
	}

	bool CANThread::Launch()
	{
		if (mbRunning)
			return true;

		DWORD dwThreadId = 0;

		ResetEvent(mStopEvent);

		mhThreadHandle = CreateThread(
			NULL,
			0,
			ThreadOne,
			this,
			0,
			&dwThreadId
		);
		if (mhThreadHandle != NULL)
		{
			mdwThreadID = dwThreadId;
			mbRunning = true;
		}

		return mbRunning;
	}

}
