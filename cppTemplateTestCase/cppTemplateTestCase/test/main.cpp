#include "test.h"

void basic_test()
{
	TEST(max1)();
	TEST(max2)();
}

int main()
{
	basic_test();
	system("pause");
	return 0;
}