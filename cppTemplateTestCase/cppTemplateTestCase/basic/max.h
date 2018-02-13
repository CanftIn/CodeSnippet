#pragma once

#include "../test/global.h"
#include <iostream>
#include <string>

// maximum of two int values:
int max(int a, int b)
{
	return  b < a ? a : b;
}

template<typename T>
T max(T a, T b)
{
	// if b < a then yield a else yield b
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