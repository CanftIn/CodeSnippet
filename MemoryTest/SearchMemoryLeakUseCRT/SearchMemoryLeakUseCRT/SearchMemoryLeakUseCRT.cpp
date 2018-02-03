#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>  


int main()
{
	int* p = new int(2);

	// Report memory leak until now.
	_CrtDumpMemoryLeaks();

	delete p;
	return 0;
}