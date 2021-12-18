#include <stdio.h>
#define N 1000

int main() {
	FILE *inp = fopen("lab1.txt", "r");
	FILE *out = fopen("lab1-copy-1-19.txt", "w");
	char buff[N];
	while (fgets(buff, N, inp)) {
		fputs(buff, out);
	}
	fclose(inp);
	fclose(out);
	return 0;
}