#include "ext/io.h"
#include "base/gtype.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct contact {
  char *number;
  char *fullname;
} *contact_t;

void print_contact(gtype v) {
  printf("Chi tiết liên lạc: \n");
  printf("Sđt: %s\n", ((contact_t)(v.v))->number);
  printf("Họ và tên: %s\n", ((contact_t)(v.v))->fullname);
}

int main() {
  gtype v, u;
  printf("Nhập 1 số nguyên: ");
  scanf("%ld", &v.l);
  printf("Bạn đã nhập v: %ld\n", v.l);
  printf("Nhập 1 số nguyên khac: ");
  scanf("%ld", &u.l);
  printf("Bạn đã nhập u: %ld\n", u.l);
  gtype_swap(v, u);
  printf("After swap: v = %ld, u = %ld\n", v.l, u.l);
  printf("gtype_print_l v = ");
  gtype_print_l(v);
  printf("Nhập 1 số thực: ");
  scanf("%lf", &v.d);
  printf("Bạn đã nhập: %f\n", v.d);
  contact_t c = calloc(1, sizeof(struct contact));
  printf("Nhập sđt: ");
  clear_stdin();
  remove_tail_lf(cgetline(&(c->number), 0, stdin));
  printf("Nhập họ và tên: ");
  remove_tail_lf(cgetline(&(c->fullname), 0, stdin));
  v.v = c;
  print_contact(v);
  free(c->number);
  free(c->fullname);
  free(c);
  return 0;
}