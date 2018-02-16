#include <iostream>
#include <typeinfo>

using namespace std;
#if 0
int main()
{
	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto i = begin(arr);
	std::cout << "type of a: " << typeid(i).name() << std::endl;

}
#endif