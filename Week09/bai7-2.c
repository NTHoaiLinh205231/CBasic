#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ext/io.h"

typedef char* pchar;
#define to_s(p) (*(const pchar*)p)
int cmp_inc_s(const void *a, const void *b) { //*a co kieu char
	printf("%s  %s\n", to_s(a), to_s(b));
	return strcmp(to_s(a), to_s(b));
}

int main() {
	pchar *a;
	int n = 0;
	printf("Nhap so n nguyen duong: ");
	scanf("%d", &n);
	a = malloc(n * sizeof(pchar)); //char *a[n]
	printf("Nhap %d chuoi ky tu:\n", n);
	pchar buff = NULL;
	clear_stdin();
	for (int i = 0; i < n; i++) {
		if (cgetline(&buff, 0, stdin)) {
			remove_tail_lf(buff);
			a[i] = strdup(buff);
		}
	}
	//a[i] co kieu char *
	//cmp_inc_s nhan dia chi cua a[i]
	//=> kieu dung char **
	free(buff);
	qsort(a, n, sizeof(a[0]), cmp_inc_s);
	printf("Sau khi sap xep:\n");
	for (int i = 0; i < n; i++) {
		printf("a[%d] = %s\n", i, a[i]);
	}
	for (int i = 0; i<n; i++) {
		free(a[i]);
	}
	free(a);
	return 0;
}