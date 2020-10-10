#include <iostream>
#include <queue>
#include <functional>
#include <vector>

template <typename T>
void print_queue(T& q) {
  while (!q.empty()) {
    std::cout << q.top() << " ";
    q.pop();
  }
  std::cout << "\n";
}

int main() {
  std::priority_queue<int> q;
  for (int n : {1,8,5,6,3,4,0,9,7,2})
    q.push(n);
  std::priority_queue<int> q_copy = std::move(q);
  print_queue(q);
  print_queue(q_copy);

  int i = 10;
  int j = 30;
  const int* temp = &i;
  std::cout << *temp << std::endl;
  std::cout << temp << std::endl;
  i = 14;
  temp = &j;
  std::cout << *temp << std::endl;
  std::cout << temp << std::endl;
  int a = 50;
  int* const p = &a;
  std::cout << *p << std::endl;
  *p = 20;
  std::cout << *p << std::endl;
  std::cout << a << std::endl;
}