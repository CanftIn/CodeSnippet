#include <tuple>
#include <string>
#include <type_traits>
#include <iostream>

template <typename T1, typename T2, typename T3>
class my_wrapper {
	T1 t1;
	T2 t2;
	T3 t3;

public:
	my_wrapper(T1 t1_, T2 t2_, T3 t3_)
		: t1{ t1_ }, t2{ t2_ }, t3{ t3_ }
	{}

	/* … */
};

template <typename T>
struct sum {
	T value;

	template <typename ... Ts>
	sum(Ts&& ... values) : value{ (values + ...) } {}
};

//msvc not support
//gcc7.1 support
//g++ -std=c++1z -Wall -o xxx xxx.cpp

#if 0
template <typename ... Ts>
sum(Ts&& ... ts)->sum<std::common_type_t<Ts...>>;
#endif

#if 0
int main()
{
	my_wrapper wrap(123, 4.56, std::string{ "foo" });

	std::pair  pair(123, std::string{ "string" });
	std::tuple tuple(123, 4.56, std::string{ "string" });

	sum s{ 1u, 2.0, 3, 4.0f };
	sum string_sum{ std::string{ "abc" }, "def" };

	std::cout << s.value << '\n'
		<< string_sum.value << '\n';
}
#endif