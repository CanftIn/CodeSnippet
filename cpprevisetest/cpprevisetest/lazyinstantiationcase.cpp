#include <iostream>

template<typename T>
class _aTMP {
public:
    void f1() { std::cout << "f1()\n"; }
    void f2() { std::ccccout << "f2()\n"; } // 敲错键盘了，语义错误：没有 std::ccccout
};
#if 0
int main(){
    _aTMP<int> a;
    a.f1();
    // a.f2(); // 这句代码被注释时，aTMP<int>::f2() 不被实例化，从而上面的错误被掩盖!
    std::cin.get(); return 0;
}
#endif

// 计算 N 的阶乘 N!
template<int N>
class __aTMP {
public:
	enum { ret = N == 0 ? 1 : N * __aTMP<N - 1>::ret }; // Lazy Instantiation，将产生无限递归! //可用来测试编译器递归最大深度
};
// 计算 N 的阶乘 N!
template<int N>
class aTMP {
public:
	enum { ret = N * aTMP<N - 1>::ret };
};

template<>
class aTMP<0> {
public:
	enum { ret = 1 };
};
#if 0
int main() {
	std::cout << aTMP<10>::ret << '\n';
	std::cin.get(); return 0;
}
#endif