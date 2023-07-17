#include <Windows.h>
#include <iostream>

int g_Count = 0;
int g_ESP;
#pragma optimize("", off)

void deadloop()
{
	g_Count++;
	char szMsg[512] = "";
	_asm mov g_ESP, esp;
	std::cout << g_ESP << std::endl;
	deadloop();
}

#pragma optimize("", on)

int main(int argc, char **argv)
{
	std::cout << "stack overflow test" << std::endl;
	deadloop();
	return g_Count;
}