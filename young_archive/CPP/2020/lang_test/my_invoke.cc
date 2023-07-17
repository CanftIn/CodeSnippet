#include <iostream>
#include <functional>
// ========================================================================
// 第三步
// 调用普通函数的版本
struct _InvokeFunction {
    template<typename _Callable, typename... _Types>
    static auto _Call(_Callable&& obj, _Types&&... argv) {
        return obj(std::forward<_Types>(argv)...);
    }
};
// 调用成员函数版本
struct _InvokeMemFunc {
    template<typename _Callable, typename _Obj, typename... _Types>
    static auto _Call(_Callable&& fn, _Obj&& obj, _Types&&... argv) ->
        decltype((obj->*fn)(std::forward<_Types>(argv)...)) {
        return (obj->*fn)(std::forward<_Types>(argv)...);
    }
    // 这里和stl当中方法不一样，这里采用使用SFINAE技术
    // 编译器会自动选择两者当中可调用的版本
    template<typename _Callable, typename _Obj, typename... _Types>
    static auto _Call(_Callable&& fn, _Obj&& obj, _Types&&... argv) ->
        decltype((obj.*fn)(std::forward<_Types>(argv)...)) {
        return (obj.*fn)(std::forward<_Types>(argv)...);
    }
};
// 调用成员变量
struct _InvokeMemObj {
    template<typename _Callable, typename _Obj>
    static auto _Call(_Callable&& fn, _Obj&& obj) ->
        decltype((obj->*fn)) {
        return (obj->*fn);
    }
    template<typename _Callable, typename _Obj>
    static auto _Call(_Callable&& fn, _Obj&& obj) ->
        decltype((obj.*fn)) {
        return (obj.*fn);
    }
};
// =========================================================================
// 第二步
// 第二层，筛选多参数普通函数，成员函数，数据成员
// 暂时依赖标准库的萃取技术
template<typename _Callable, 
    typename _FirstTy,
    typename _Decayed = typename std::decay<_Callable>::type,
    bool _Is_MemFun = std::is_member_function_pointer<_Decayed>::value,
    bool _Is_MemObj = std::is_member_object_pointer<_Decayed>::value>
struct _Invoke1;
// 成员函数，标准库当中传递
// _FirstTy的作用是用来判断 _Callable的Class是否是_FirstTy的Class或者Parent Class
// 这里为了简化不再判断
template<typename _Callable, typename _FirstTy, typename _Decayed>
struct _Invoke1<_Callable, _FirstTy, _Decayed, true, false> :
    _InvokeMemFunc {
};
// 成员变量
template<typename _Callable, typename _FirstTy, typename _Decayed>
struct _Invoke1<_Callable, _FirstTy, _Decayed, false, true> :
    _InvokeMemObj {
};
// 普通函数
template<typename _Callable, typename _FirstTy, typename _Decayed>
struct _Invoke1<_Callable, _FirstTy, _Decayed, false, false> :
    _InvokeFunction {
};
// =========================================================================
// 第一步
// 本层先把无参数的直接筛选出来了
template<typename _Callable, typename... _Types>
struct _Invoke;
// 无参数，必定是一个普通函数
template<typename _Callable>
struct _Invoke<_Callable> :
    _InvokeFunction {
};
// 有一个或多个参数，可能是普通函数，成员函数，数据成员
template<typename _Callable, typename _FirstTy, typename... _Types>
struct _Invoke<_Callable, _FirstTy, _Types...> :
    _Invoke1<_Callable, _FirstTy> {
};
// 通过Invoke函数进行一层封装，使其使用更加贴合实际
template<typename _Callable, typename... _Types>
auto Invoke(_Callable&& obj, _Types&&... argv) {
    return _Invoke<_Callable, _Types...>::_Call(
        std::forward<_Callable>(obj), 
        std::forward<_Types>(argv)...);
}
// ========================================================================
// 测试代码
void sum(int a, int b, int c) {
    std::cout << a + b + c<< std::endl;
}
struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_ + i << '\n'; }
    int num_;
};
int main() {
    Foo foo(123);
    Invoke(sum, 1, 2, 3);
    Invoke([=]() {});
    Invoke(&Foo::print_add, foo, 1);
    Invoke(&Foo::print_add, &foo, 1);
    auto n = Invoke(&Foo::num_, &foo);
    auto n1 = Invoke(&Foo::num_, foo);
    return 0;
}