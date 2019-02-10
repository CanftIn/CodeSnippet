#ifndef THREAD_H_
#define THREAD_H_

#include "../Basic.h"
#include <Windows.h>

namespace CAN
{
	class CANThread
	{
	protected:
		HANDLE mhThreadHandle;
		DWORD mdwThreadID;
		bool mbRunning;

		HANDLE mStopEvent;

	public:
		CANThread() : mhThreadHandle(NULL),
			mdwThreadID(0),
			mbRunning(false)
		{
			mStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		}

		virtual ~CANThread()
		{
			if (mbRunning)
			{
				CloseHandle(mhThreadHandle);
				mbRunning = false;
			}
			CloseHandle(mStopEvent);
		}

		bool Launch();

		void StopThread()
		{
			if (mbRunning)
			{
				int iErr = SetEvent(mStopEvent);
				if (iErr == 0)
				{
					DWORD dw = GetLastError();
				}
				WaitForSingleObject(mhThreadHandle, INFINITE);
				CloseHandle(mhThreadHandle);
				mbRunning = false;
			}
		}

		inline bool IsRunning() { return mbRunning; }
		inline HANDLE GetThreadHandle() { return mhThreadHandle; }
		virtual void WorkLoop() = 0;
	};

	class CANLock
	{
	public:
		CANLock()
		{
			InitializeCriticalSection(&mCriticalSection);
		}

		virtual ~CANLock()
		{
			DeleteCriticalSection(&mCriticalSection);
		}

		void Lock()
		{
			EnterCriticalSection(&mCriticalSection);
		}
		void Unlock()
		{
			LeaveCriticalSection(&mCriticalSection);
		}

	protected:
		CRITICAL_SECTION mCriticalSection;
	};

	class CANLockApply
	{
	public:
		CANLockApply(CANLock& lock)
			: mLock(lock)
		{
			mLock.Lock();
		}
		virtual ~CANLockApply()
		{
			mLock.Unlock();
		}

		CANLockApply();
		CANLockApply& operator = (const CANLockApply&) { return *this; }

	protected:
		CANLock& mLock;
	};
}

#endif