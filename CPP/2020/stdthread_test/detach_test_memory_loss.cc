#include <thread>
#include <iostream>

struct func {
  int& i_;
  func(int& i) : i_(i) {}
  void operator () () {
    for (unsigned j = 0; j < 1000000; ++j) {
      do_something(j);
    }
  }
  void do_something(int num) {
  }
};

int main() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.join();
}