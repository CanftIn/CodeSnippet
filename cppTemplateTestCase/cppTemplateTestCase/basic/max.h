#pragma once

#include "../test/global.h"
#include <iostream>
#include <string>
#include <type_traits>
#include <functional>




// maximum of two int values:
int max(int a, int b)
{
	return  b < a ? a : b;
}
/*
template<typename T>
T max(T a, T b)
{
	// if b < a then yield a else yield b
	return  b < a ? a : b;
}
*/
/*
template<typename T1, typename T2>
auto max(T1 a, T2 b) -> decltype(b<a ? a : b)
{
	return  b < a ? a : b;
}


template<typename T1, typename T2>
auto max(T1 a, T2 b) -> typename std::decay<decltype(true ? a : b)>::type
{
	return  b < a ? a : b;
}

template<typename T1, typename T2>
std::common_type_t<T1, T2> max(T1 a, T2 b)
{
	return  b < a ? a : b;
}

template<typename T1, typename T2>
constexpr auto max(T1 a, T2 b)
{
	return  b < a ? a : b;
}

template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
	return  b < a ? a : b;
}

template<typename T1, typename T2,
	typename RT = std::decay_t<decltype(true ? T1() : T2())>>
	RT max(T1 a, T2 b)
{
	return  b < a ? a : b;
}

template<typename T1, typename T2,
	typename RT = std::common_type_t<T1, T2>>
	RT max(T1 a, T2 b)
{
	return  b < a ? a : b;
}

template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
	return  b < a ? a : b;
}

template<typename RT, typename T1, typename T2>
RT max(T1 a, T2 b)
{
	return  b < a ? a : b;
}
*/
template<typename T1, typename T2,
	typename RT = std::decay_t<decltype(true ? std::declval<T1>()
		: std::declval<T2>())>>
	RT max(T1 a, T2 b)
{
	return  b < a ? a : b;
}


void TEST(max1)()
{
	int i = 42;
	std::cout << "max(7,i):   " << ::max(7, i) << '\n';

	double f1 = 3.4;
	double f2 = -6.7;
	std::cout << "max(f1,f2): " << ::max(f1, f2) << '\n';

	std::string s1 = "mathematics";
	std::string s2 = "math";
	std::cout << "max(s1,s2): " << ::max(s1, s2) << '\n';
}

void TEST(max2)()
{
	::max(7, 42);          // calls the nontemplate for two ints
	::max(7.0, 42.0);      // calls max<double> (by argument deduction)
	::max('a', 'b');       // calls max<char> (by argument deduction)
	::max<>(7, 42);        // calls max<int> (by argument deduction)
	::max<double>(7, 42);  // calls max<double> (no argument deduction)
	::max('a', 42.7);      // calls the nontemplate for two ints
}

void TEST(max3)()
{
	int a = 10;
	int b = 20;
	int& c = a;
	int& d = b;
	int&& e = 30;
	int&& f = 40;
	std::cout << max<int>(c, d) << '\n';
	std::cout << max<int>(e, f) << '\n';
}

void f(int& n1, int& n2, const int& n3)
{
	std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	++n1; // increments the copy of n1 stored in the function object
	++n2; // increments the main()'s n2
		  // ++n3; // compile error
}

void TEST(ref)()
{
	int n1 = 1, n2 = 2, n3 = 3;
	std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
	n1 = 10;
	n2 = 11;
	n3 = 12;
	std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	bound_f();
	std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	f(n1, n2, n3);
	n1 = 30;
	n2 = 31;
	n3 = 32;
	f(n1, n2, n3);
}