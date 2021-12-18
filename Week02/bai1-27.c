#include <stdio.h>

int main() {
	FILE *inp = fopen("product1.txt", "r");
	if (!inp) {
		printf("Loi mo tep.\n");
		return 1;
	}
	int stt;
	char name[1024];
	double price;
	printf("%-8s%-32s%10s\n", "No", "Product Name", "Price");
	for ( ; ; ) {
		int ret = fscanf(inp, "%d%s%lf", &stt, name, &price);
		if (ret != 3) {
			break;
		}
		printf("%-8d%-32s%15.2f\n", stt, name, price);
	}
	fclose(inp);
	return 0;
}
