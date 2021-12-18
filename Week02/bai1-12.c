#include <stdio.h>

int main() {
	FILE *inp = fopen("lab1.txt", "r");
	FILE *out = fopen("lab1-copy.txt", "w");
	int c;
	while ((c = fgetc(inp)) != EOF) {
		fputc(c, out);
	}
	fclose(inp);
	fclose(out);
}