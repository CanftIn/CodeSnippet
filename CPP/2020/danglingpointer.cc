#include <cstdlib>

extern "C" void printf(const char* fmt, ...);

class Dog {
public:
  virtual void bark() { }
};

class Cat {
public:
  int id_;
  int color_;
  void meow() { }
};

const int ARRAY_LEN = 5;

int main() {
  int* array_ptr1 = (int*)malloc(ARRAY_LEN * sizeof(int));
  int* array_ptr2 = array_ptr1;
  printf("int* array_ptr1 = %p\n", array_ptr1);
  free(array_ptr1);

  Dog* dog = (Dog*)malloc(sizeof(Dog));
  printf("Dog* dog = %p\n", dog);

  free(array_ptr2);

  Cat* cat = (Cat*)malloc(sizeof(Cat));
  printf("Cat* cat = %p\n", cat);

  cat->id_ = 1;
  dog->bark();

  return 0;
}