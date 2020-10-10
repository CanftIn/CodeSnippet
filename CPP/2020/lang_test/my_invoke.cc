#include <iostream>
#include <functional>

struct InvokeFunction {
  template <typename Callable, typename... Types>
  static auto Call(Callable&& obj, Types&&... argv) {
    return obj(std::forward<Types>(argv)...);
  }
};

template <typename Callable, typename... Types>
struct Invoke;

template <typename Callable>
struct Invoke<Callable> : InvokeFunction
{ };

template <typename Callable, typename FirstTy, typename... Types>
struct Invoke<Callable, FirstTy, Types...> :