// Minh họa sử dụng setsize

#include <stdio.h>
#include "base/arr.h"

long sum(arr_t(int) a) {
  long s = 0;
  for (int i = 0; i < arr_size(a); ++i) {
    s += ARR(a)[i];
  }
  return s;
}

int main() {
  arr_decl(a, 0, int); //= arr_t(int) a = arr_create(10, int);
  arr_set_size(a, 10);
  printf("size = %zu\n", arr_size(a));
  for (int i = 0; i < arr_size(a); ++i) {
    ARR(a)[i] = i;
  }

  //  Thay đổi kích thước mảng
  arr_set_size(a, 20);
  for (int i = 0; i < arr_size(a); ++i) {
    printf("a[%d] = %d\n", i, ARR(a)[i]);
  }
  printf("size = %zu\n", arr_size(a));
  return 0;
}