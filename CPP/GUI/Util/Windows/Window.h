#ifndef WINDOW_H_
#define WINDOW_H_

#include "../Basic.h"
#include "Base.h"
#include "Event.h"

#include <Windows.h>

namespace CAN
{
	class Window : implements Object
	{
	protected:
		HWND mhWnd;
		uint miWidth, miHeight;
		wstring mstrTitle;
		bool mbActive;

	public:
		NotifyEvent mMainLoopEvent;
		NotifyEvent mInitializeEvent;
		NotifyEvent mReleaseEvent;
		ResizeEvent mResizeEvent;
		MouseEvent  mMouseEvent;

	public:
		Window()
		{
		}

		virtual bool Create(const wstring& strTitle,
			const uint iResX,
			const uint iResY);

		virtual void Destroy();

		inline HWND GetHandle() const { return mhWnd; }

		bool IsActive() const { return mbActive; }
		void SetActive(const bool active) { mbActive = active; }

		virtual void InvokeMainLoop() { mMainLoopEvent.Invoke(this, EventArgs()); }

		inline void SetMainLoop(const NotifyEvent& mainLoopEvent)
		{
			mMainLoopEvent = mainLoopEvent;
		}

		inline void SetInit(const NotifyEvent& initEvent) 
		{
			mInitializeEvent = initEvent;
		}

		inline void SetResize(const ResizeEvent& resizeEvent)
		{
			mResizeEvent = resizeEvent;
		}

		inline void SetRelease(const NotifyEvent& releaseEvent)
		{
			mReleaseEvent = releaseEvent;
		}

		virtual bool ProcessMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:
		bool RegisterWindowClass();
	};

	class GLWindow : implements Window
	{
	protected:
		HGLRC mhRC;
		HDC mhDC;

		bool Create(const wstring& strTitle, const uint iWidth, const uint iHeight);
		virtual void Destroy();

	public:
		void InvokeMainLoop()
		{
			mMainLoopEvent.Invoke(this, EventArgs());
			SwapBuffers(mhDC);
		}
	};
}

#endif