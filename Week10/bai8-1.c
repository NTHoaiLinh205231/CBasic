#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#define N 10000

#define to_d(x) (*(const double *)x)
int cmp_d(const void *a, const void *b) {
	if (to_d(b) < to_d(a)) {
    return -1;
  } else if (to_d(b) > to_d(a)) {
    return 1;
  }
  return 0;
}
int main(int argc, char *argv[]) {
	if ((argc != 2)) {
		printf("Usage: ./prog text.txt\n");
		return 1;
	}
	int k;
	printf("Nhap k: ");
	scanf("%d", &k);

	clock_t start = clock();
	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Loi mo tep %s\n", argv[1]);
		return 1;
	}
	double a[N];
	int idx = 0;
	while (fscanf(f, "%lf", &a[idx]) == 1) {
		//printf("%g  ", a[idx]);
		idx++;
	}

	qsort(a, idx, sizeof(double), cmp_d);
	printf("Top k:\n");
	for (int i = 0; i < k; i++) {
		printf("%g\n", a[i]);
	}
	fclose(f);
	clock_t end = clock();
	double time_process = (double) (end - start)/CLOCKS_PER_SEC;
	printf("Thoi gian xu ly: %lf\n", time_process);
	return 0;
}
