#include <stdio.h>

int main() {
	FILE *inp = fopen("product.txt", "r");
	int n;
	fscanf(inp, "%d", &n);
	int stt;
	char name[1024];
	double price;
	printf("%-8s%-32s%10s\n", "No", "Product Name", "Price");
	for (int i = 0; i < n; ++i) {
		fscanf(inp, "%d%s%lf", &stt, name, &price);
		printf("%-8d%-32s%15.2f\n", stt, name, price);
	}

	fclose(inp);
	return 0;
}
/*
#include <stdio.h>

int main() {
	FILE *inp = fopen("product1.txt", "r");
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
*/
/*
#include <stdio.h>

int main() {
	FILE *inp = fopen("product1.txt", "r");
	int stt;
	char name[1024];
	double price;
	printf("%-8s%-32s%10s\n", "No", "Product Name", "Price");
	for ( ; ; ) {
		int ret = fscanf(inp, "%d%s%lf", &stt, name, &price);
		if (ret == EOF) {
			break;
		}
		printf("%-8d%-32s%15.2f\n", stt, name, price);
	}
	fclose(inp);
	return 0;
}
*/