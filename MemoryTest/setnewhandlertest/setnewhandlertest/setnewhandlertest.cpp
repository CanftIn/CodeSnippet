// setnewhandlertest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <new>
#include <iostream>

using namespace std;

void handler()
{
	cout << "alloc memory error!" << endl;
	set_new_handler(nullptr);
}

int main()
{
	set_new_handler(handler);
	try
	{
		while (true)
		{
			new int[100000000ul];
		}
	}
	catch (const bad_alloc& e)
	{
		cout << e.what() << endl;
	}
    return 0;
}

