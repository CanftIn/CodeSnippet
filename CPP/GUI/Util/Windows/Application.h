#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "../Basic.h"
#include "Base.h"
#include "Window.h"

#include <Windows.h>

namespace CAN
{
	//class Window;

	class Application : implements Object
	{
	private:
		static HINSTANCE InstHandle;
		static Window* pMainWindow;

	public:
		static const wchar_t* WinClassName;

	public:
		static void Init(HINSTANCE inst) { InstHandle = inst; }
		inline static HINSTANCE GetInstanceHandle() { return InstHandle; }
		inline static Window* GetMainWindow() { return pMainWindow; }

		static int Run(Window* pWindow);
		static void Dispose();
	};
}

#endif