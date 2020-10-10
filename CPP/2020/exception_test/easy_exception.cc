#include <iostream>
#include <exception>

using namespace std;

struct MyException : public exception {
  const char* what() const throw() {
    return "My C++ Exception";
  }
};

int main() {
  try {
    throw MyException();
  } catch (MyException& e) {
    cout << "MyException caught" << std::endl;
    cout << e.what() << std::endl;
  } catch (std::exception& e) {
    cout << "other exception" << std::endl;
    cout << e.what() << std::endl;
  }
}