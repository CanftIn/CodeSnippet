#include <iostream>
#include <cstdlib>
#include <exception>

using namespace std;

class OutOfRange {
public:
  OutOfRange() : m_flag(1) {}
  OutOfRange(int len, int index) : m_len(len), m_index(index), m_flag(2) {}

  void what() const {
    if(m_flag == 1){
      cout << "Error: empty array, no elements to pop." << endl;
    } else if (m_flag == 2) {
      cout << "Error: out of range( array length " << m_len << ", access index " << m_index << " )" << endl;
    } else {
      cout << "Unknown exception." << endl;
    }
  }

private:
  int m_flag;
  int m_len;
  int m_index;
}