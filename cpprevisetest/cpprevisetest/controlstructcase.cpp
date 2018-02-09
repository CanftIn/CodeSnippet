﻿#include <iostream>

// 通例为空，若不匹配特例将报错，很好的调试手段（这里是 bool 就无所谓了）
template<bool c, typename Then, typename Else> class IF_ { };
template<typename Then, typename Else>
class IF_<true, Then, Else> { public: typedef Then reType; };
template<typename Then, typename Else>
class IF_<false, Then, Else> { public: typedef Else reType; };

// 隐含要求： Condition 返回值 ret，Statement 有类型 Next
template<template<typename> class Condition, typename Statement>
class WHILE_ {
	template<typename Statement> class STOP { public: typedef Statement reType; };
public:
	typedef typename
		IF_<Condition<Statement>::ret,
		WHILE_<Condition, typename Statement::Next>,
		STOP<Statement>>::reType::reType
		reType;
};

const int len = 4;
typedef
IF_<sizeof(short) == len, short,
	IF_<sizeof(int) == len, int,
	IF_<sizeof(long) == len, long,
	IF_<sizeof(long long) == len, long long,
	void>::reType>::reType>::reType>::reType
	int_my; // 定义一个指定字节数的类型

//typedef IF_<sizeof(long long) == len, short, void>::reType not_my; //error

//int main()
//{
	//std::cout << sizeof(not_my) << '\n';
//}

// 计算 1^e+2^e+...+n^e
template<int n, int e>
class sum_pow {
	template<int i, int e> class pow_e { public: enum { ret = i*pow_e<i, e - 1>::ret }; };
	template<int i> class pow_e<i, 0> { public: enum { ret = 1 }; };
	// 计算 i^e，嵌套类使得能够定义嵌套模板元函数，private 访问控制隐藏实现细节
	template<int i> class pow { public: enum { ret = pow_e<i, e>::ret }; };
	template<typename stat>
	class cond { public: enum { ret = (stat::ri <= n) }; };
	template<int i, int sum>
	class stat {
	public: typedef stat<i + 1, sum + pow<i>::ret> Next;
			enum { ri = i, ret = sum };
	};
public:
	enum { ret = WHILE_<cond, stat<1, 0>>::reType::ret };
};

#if 0
int main() {
	std::cout << sum_pow<10, 2>::ret << '\n';
	std::cin.get(); return 0;
}
#endif

// 最小公倍数，普通函数
int lcm(int a, int b) {
	int r, lcm = a*b;
	while (r = a%b) { a = b; b = r; } // 因为用可变的存储，不能写成 a=b; b=a%b;
	return lcm / b;
}
// 递归函数版本
int gcd_r(int a, int b) { return b == 0 ? a : gcd_r(b, a%b); } // 简洁
int lcm_r(int a, int b) { return a * b / gcd_r(a, b); }

// 模板版本
template<int a, int b>
class lcm_T {
	template<typename stat>
	class cond { public: enum { ret = (stat::div != 0) }; };
	template<int a, int b>
	class stat { public: typedef stat<b, a%b> Next; enum { div = a%b, ret = b }; };
	static const int gcd = WHILE_<cond, stat<a, b>>::reType::ret;
public:
	static const int ret = a * b / gcd;
};
// 递归模板版本
template<int a, int b>
class lcm_T_r {
	template<int a, int b> class gcd { public: enum { ret = gcd<b, a%b>::ret }; };
	template<int a> class gcd<a, 0> { public: enum { ret = a }; };
public:
	static const int ret = a * b / gcd<a, b>::ret;
};

#if 0
int main() {
	std::cout << lcm(100, 36) << '\n';
	std::cout << lcm_r(100, 36) << '\n';
	std::cout << lcm_T<100, 36>::ret << '\n';
	std::cout << lcm_T_r<100, 36>::ret << '\n';
	std::cin.get(); return 0;
}
#endif