#include "Window.h"
#include "Application.h"

namespace CAN
{
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Window::Create(const wstring& strTitle,
		const uint iWidth,
		const uint iHeight)
	{
		mstrTitle = strTitle;
		miWidth = iWidth;
		miHeight = iHeight;

		if (!RegisterWindowClass())
			return false;

		DWORD winStyle = WS_OVERLAPPEDWINDOW;
		DWORD winStyleEX = WS_EX_CLIENTEDGE;

		RECT rect = { 0, 0, miWidth, miHeight };
		AdjustWindowRectEx(&rect, winStyle, NULL, winStyleEX);

		mhWnd = ::CreateWindowEx(
			winStyleEX,
			Application::WinClassName,
			mstrTitle.data(),
			winStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			GetDesktopWindow(),
			NULL,
			Application::GetInstanceHandle(),
			NULL
		);
		if (!mhWnd)
			return false;
		return true;
	}

	void Window::Destroy()
	{
		mReleaseEvent.Invoke(this, EventArgs());
		::UnregisterClass(Application::WinClassName, Application::GetInstanceHandle());
	}

	bool Window::ProcessMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_ACTIVATE:
			if (!HIWORD(wParam))
				SetActive(true);
			else
				SetActive(false);
			break;
		case WM_SIZE:
			mResizeEvent.Invoke(Application::GetMainWindow(), ResizeEventArgs(LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_DESTROY:
			Destroy();
			PostQuitMessage(0);
			return true;
		}
		return false;
	}

	bool Window::RegisterWindowClass()
	{
		WNDCLASSEX winClass;
		winClass.cbSize = sizeof(WNDCLASSEX);
		winClass.style = CS_OWNDC;
		winClass.lpfnWndProc = WndProc;
		winClass.cbClsExtra = 0;
		winClass.cbWndExtra = 0;
		winClass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
		winClass.hIcon = LoadIcon(0, IDI_APPLICATION);
		winClass.hCursor = LoadCursor(0, IDC_ARROW);
		winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		winClass.lpszMenuName = 0;
		winClass.lpszClassName = Application::WinClassName;
		winClass.hIconSm = LoadIcon(0, IDI_APPLICATION);

		if (!::RegisterClassEx(&winClass))
			return false;

		return true;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		bool bProcessed = false;
		Window* pWnd;
		if (pWnd = Application::GetMainWindow())
		{
			bProcessed = pWnd->ProcessMessage(hwnd, msg, wParam, lParam);
		}
		if(!bProcessed)
			return DefWindowProc(hwnd, msg, wParam, lParam);
		return 0;
	}

	bool GLWindow::Create(const wstring& strTitle, const uint iWidth, const uint iHeight)
	{
		if (!Window::Create(strTitle, iWidth, iHeight))
			return false;

		PIXELFORMATDESCRIPTOR pf =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			24,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			32,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
		mhDC = ::GetDC(GetHandle());
		int idx = ::ChoosePixelFormat(mhDC, &pf);
		::SetPixelFormat(mhDC, idx, &pf);

		mhRC = ::wglCreateContext(mhDC);
		::wglMakeCurrent(mhDC, mhRC);

		return true;
	}

	void GLWindow::Destroy()
	{
		Window::Destroy();

		::wglMakeCurrent(0, 0);
		::wglDeleteContext(mhRC);
		::ReleaseDC(mhWnd, mhDC);

		mhDC = 0;
		mhRC = 0;
	}
}