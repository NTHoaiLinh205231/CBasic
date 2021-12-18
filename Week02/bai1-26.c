#include <stdio.h>

int main() {
	int n;
	printf("Nhap n = ");
	scanf("%d", &n);
	if (n>100) {
		printf("n khong lon hon 100");
		return 1;
	}
	FILE *out = fopen("out.txt", "w");
	if (!out) {
		printf("Loi mo tep\n");
		return 1;
	}
	int a[100], sum=0;
	for (int i=0; i<n; i++) {
		scanf("%d", &a[i]);
		sum+=a[i];
	}
	for (int i=n-1; i>=0; i--) {
		fprintf(out, "%d ", a[i]);
	}
	fprintf(out, "%d ", sum);
	return 0;
}