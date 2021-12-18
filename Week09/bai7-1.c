#include <stdio.h>
#include <stdlib.h>

#define to_int(p) (*((const int*)p))

int cmp_inc_i(const void *a, const void *b) {
	return to_int(a) - to_int(b);
}

int main() {
	int n;
	printf("Nhap so phan tu: ");
	scanf("%d", &n);
	int *a = calloc(n, sizeof(int));
	printf("Nhap %d so nguyen duong:\n", n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	qsort(a, n, sizeof(int), cmp_inc_i);
	printf("Day sau khi sap xep:\n");
	for (int i = 0; i < n; i++) {
		printf("%d  ", a[i]);
	}
	printf("\n");
	free(a);
	return 0;
}