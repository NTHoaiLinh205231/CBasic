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
  arr_decl(a, 0, int);
  //arr_set_capacity(a, 15);
  //printf("capacity: %ld\n", arr_capacity(a));
  printf("Nhập vào 1 dãy số bất kỳ, nhập 0 để kết thúc nhập:\n");
  for(;;) {
    int v;
    scanf("%d", &v);
    if (v == 0) {
      break;
    }
    arr_append(a, v);
  }
  printf("Tổng các số đã nhập: %ld\n", sum(a));
  printf("Danh sách các số theo chiều ngược lại: ");
  for (long i = arr_size(a) - 1; i >= 0; --i) {
    printf(" %d", ARR(a)[i]);
  }
  printf("\n");
  int *p;
  *p = 5;
  printf("element %dth is %d\n", 5, elem(a, 4));
  printf("element %dth is %d\n", *p, *elem_ref(a, 4));
  printf("size: %ld\n", arr_size(a));
  printf("capacity: %ld\n", arr_capacity(a));
  //arr_set_capacity(a, 30);
  //printf("after arr_set_capacity: %ld\n", arr_capacity(a));

  printf("arr_elem_sz: %ld\n", arr_elem_sz(a));
  printf("arr_inc: %ld\n", arr_inc(a));

  arr_free(a);
  return 0;
}
//Nhung dieu chua hieu: capacity, inc