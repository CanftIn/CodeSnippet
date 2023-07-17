#include "Application.h"
#include "Window.h"


namespace CAN
{
	HINSTANCE Application::InstHandle = NULL;
	const wchar_t* Application::WinClassName = L"CANWinClass";
	Window* Application::pMainWindow = nullptr;

	int Application::Run(Window* pWindow)
	{
		HWND hWnd = pWindow->GetHandle();
		pMainWindow = pWindow;
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		pMainWindow->mInitializeEvent.Invoke(pMainWindow, EventArgs());

		MSG msg;
		while (true)
		{
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message != WM_QUIT)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					break;
			}
			else if (pWindow->IsActive())
			{
				pMainWindow->InvokeMainLoop();
			}
		}

		pMainWindow->mReleaseEvent.Invoke(pMainWindow, EventArgs());
		Dispose();

		return (int)msg.wParam;
	}

	void Application::Dispose()
	{
		if (pMainWindow)
			delete pMainWindow;

		assert(!_CrtDumpMemoryLeaks());
	}
}