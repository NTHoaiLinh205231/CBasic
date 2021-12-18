#include "cgen.ic"

long *bns_keys(bn_tree_t t, long *n) {
  *n = bn_size(t);
  long *a = calloc(*n, sizeof(long));
  int i = 0;
  bn_traverse_lnr(cur, t) {
    a[i] = bns_node_g_key(cur).i; 
    i++;
  }
  return a;
}

int main() {
  bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_i);
  int v;
  printf("Nhap vao mot day so nguyen khong am (nhap 1 so am bat ky de ket thuc nhap):\n");
  for (;;) {
    scanf("%d", &v);
    if (v < 0) {
      break;
    }
    bns_insert_g(t, gtype_i(v));
  }
  bns_pprint(t, gtype_print_i);
  printf("Các số theo thứ tự tăng dần: ");
  long n;
  long *a = bns_keys(t, &n);
  for (int i = 0; i < n; i++) {
    printf("%ld  ", a[i]);
  }
  printf("\n");
  bn_free_tree(&t);
  return 0;
}
//gcc -o prog bai6-1.c -I /media/sf_CBasic/cgen