#include <stdio.h>
#include <stdlib.h>
#include "cgen.h"

#define to_int(p) (*((const int*)p))
int cmp_inc_i(const void *a, const void *b) {
  return to_int(a) - to_int(b);
}

int binsearch(int l, int r, int *a, int q) {
	if (l >= r) {
		return 0;
	}
	int i = (l + r)/2;
	if (a[i] > q) {
		return binsearch(l, i, a, q);
	} else if (a[i] < q) {
		return binsearch(i+1, r, a, q);
	}
	return 1;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./prog inp.txt 101\n");
		return 1;
	}
	int q;
	sscanf(argv[2], "%d", &q);
	FILE *f = fopen(argv[1], "r");
	int n;
	fscanf(f, "%d", &n);
	int *a = malloc(sizeof(int) *n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", a + i);
	}
	printf("n = %d, q = %d\n", n, q);

	int c1 = 0, c2 = 0;
	BENCH("Vet can", 10,
		c1 = 0;
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (a[i] + a[j] == q) {
					//printf("%d + %d\n", a[i], a[j]);
					c1++;
				}
			}
		}
	);
	printf("So cap a[i] +a[j] = q: %d\n", c1);

	BENCH("Tim kiem nhi phan", 10,
		c2 = 0;
		qsort(a, n, sizeof(a[0]), cmp_inc_i);
		/*for (int i = 0; i < n; ++i)	{
			printf(" %d", a[i]);
		}
		printf("\n");*/
		for (int i = 0; i < n - 1; ++i) {
			if (binsearch(i+1, n, a, q - a[i])) {
				//printf("%d \n", a[i]);
				c2++;
			}
		}
	);	
	printf("So cap a[i] +a[j] = q: %d\n", c2);
	free(a);
	fclose(f);
	return 0;
}