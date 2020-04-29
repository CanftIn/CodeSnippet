#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <unordered_map>

struct S {
  std::string first_name;
  std::string last_name;
};

bool operator == (const S& lhs, const S& rhs) {
  return lhs.first_name == rhs.first_name && lhs.last_name == rhs.last_name;
}

struct MyHash {
  std::size_t operator () (S const& s) const {
    std::size_t h1 = std::hash<std::string>{}(s.first_name);
    std::size_t h2 = std::hash<std::string>{}(s.last_name);
    return h1 ^ (h2 << 1);
  }
};

namespace std {
  template <>
  struct hash<S> {
    using argument_type = S;
    using result_type = std::size_t;
    result_type operator () (argument_type const& s) const {
      result_type const h1 (std::hash<std::string>{}(s.first_name));
      result_type const h2 (std::hash<std::string>{}(s.last_name));
      return h1 ^ (h2 << 1);
    }
  };
}

int main() {
  std::string str = "fuck you again...";
  std::size_t st_hash = std::hash<std::string>{}(str);
  std::cout << "hash(" << std::quoted(str) << ") = " << st_hash << std::endl;

  S obj = { "Hubert", "Farnsworth"};
  // 使用独立的函数对象
  std::cout << "hash(" << std::quoted(obj.first_name) << ',' 
            << std::quoted(obj.last_name) << ") = "
            << MyHash{}(obj) << " (using MyHash)\n                           or "
            << std::hash<S>{}(obj) << " (using std::hash) " << '\n';
}


