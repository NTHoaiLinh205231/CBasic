#include <stdio.h>
#define N 1000

int main() {
	FILE *inp = fopen("lab1.txt", "r");
	FILE *out = fopen("lab1-copy-1-20.txt", "w");
	char buff[N];
	int n=0;
	while (fgets(buff, N, inp)) {
		n++;
		fputs(buff, out);
	}
	printf("So dong: %d\n", n);
	fclose(inp);
	fclose(out);
	return 0;
}