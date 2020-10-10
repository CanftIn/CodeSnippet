#include <iostream>
#include <functional>

template <typename T, typename Func>
void for_each(T* begin, T* end, const Func& f) {
  while (begin != end) {
    f(*begin++);
  }
}

template <typename T>
void print(const T& x) {
  std::cout << x << " ";
}

template <typename T>
struct Print {
  void operator () (const T& x) const {
    std::cout << x << " ";
  }
};
/*
template <typename T, typename Func, typename... Args>
void for_each_ex(T* begin, T* end, const Func& f, const Args&... args) {
  while (begin != end)
    std::invoke(f, args..., *begin++);
}
*/
template <typename T>
struct print_exciting {
  mutable int count = 0;
  void print(const T& x) const {
    std::cout << count << " : " << x << std::endl;
    count++;
  }
};

template <typename T, typename Func, typename C>
void for_each_more_ex(T* begin, T* end, Func C::* f, const C& obj) {
  while (begin != end) {
    (obj.*(f))(*begin++);
  }
}

int main() {
  int arr[5] = {1, 2, 3, 4, 5};
  for_each(arr, arr + 5, print<int>);
  for_each(arr, arr + 5, Print<int>{});
  //for_each_ex(arr, arr + 5, &print_exciting<int>::print, print_exciting<int>());
  for_each_more_ex(arr, arr + 5, &print_exciting<int>::print, print_exciting<int>());
  return 0;
}