#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

template <typename Iterator, typename T>
struct accumulate_block {
  void operator () (Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

int main() {
  std::vector<int> vi;
  for(int i = 0; i < 10; ++i) {
      vi.push_back(10);
  }
  int sum = 0;
  sum = std::accumulate(vi.begin(), vi.end(), sum);
  std::cout<<"sum="<<sum<<std::endl;
}