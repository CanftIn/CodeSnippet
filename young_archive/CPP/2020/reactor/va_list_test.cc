#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void va_list_func(const char* fmt, ...) {
  va_list arglist;
  va_start(arglist, fmt);
  vfprintf(stdout, fmt, arglist);
  //va_end(arglist);
}

int main() {
  int a = 1;
  int b = 2;
  int c = 3;
  va_list_func("%d, %d, %d\n", a, b, c);
  return 0;
}