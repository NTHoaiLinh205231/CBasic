#include "cgen.h"

int gtype_min_d(gtype v1, gtype v2) {
  if (v1.d < v2.d) {
    return 1;
  } else if (v1.d > v2.d) {
    return -1;
  }
  return 0;
}

/*#define N 10000000
#define to_d(x) (*(const double *)x)
int cmp_d(const void *a, const void *b) {
  if (to_d(b) < to_d(a)) {
    return -1;
  } else if (to_d(b) > to_d(a)) {
    return 1;
  }
  return 0;
}

void topk_sort(const char *fname, int k) {
  FILE *f = fopen(fname, "r");
  double b[N];
  int idx = 0;
  while (fscanf(f, "%lf", &b[idx]) == 1) {
    printf("%g  ", b[idx]);
    idx++;
  }
  qsort(b, idx, sizeof(double), cmp_d);
  printf("\nTop k:\n");
  for (int i = 0; i < k; i++) {
    printf("%g\n", b[i]);
  }
  fclose(f);
}*/

void topk_p1w(const char *fname, int k) {
  FILE *f = fopen(fname, "r");
  double val = 0;
  p1w_t q = p1w_create(gtype_min_d);
  int cc = 0;
  while (fscanf(f, "%lf", &val) == 1) {
    ++cc;
    if (cc <= k) {
      p1w_enqueue(q, gtype_d(val));
    } else if (val > p1w_peek(q).d) {
      p1w_dequeue(q);
      p1w_enqueue(q, gtype_d(val));
    }
  }
  fclose(f);
  gtype *a = P1WARR(q);
  printf("\nTop k:\n");
  for (int i = 0; i < k; ++i) {
    printf("%f\n", a[i].d);
  }
  //free(a);
  //p1w_free(q);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./prog inp.txt 10\n");
    return 1;
  }
  int k = 0;
  sscanf(argv[2], "%d", &k);
  //BENCH("Thoi gian chay sap xep: ", 1, topk_sort(argv[1], k));
  BENCH("Thoi gian chay hang doi: ", 1, topk_p1w(argv[1], k));
  return 0;
}