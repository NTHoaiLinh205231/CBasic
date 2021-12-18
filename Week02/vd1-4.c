#include <stdio.h>
int main(int argc, char const *argv[])
{
	FILE *inp = fopen("input.txt", "r");
	if (!inp) {
		printf("Loi mo tep input.txt.\n");
		return 1;
	}
	FILE *out = fopen("output.txt", "w");
	if (!out) {
		printf("Loi mo tep output.txt.\n");
		return 1;
	}
	int c;
	while ((c=fgetc(inp)) != EOF) {
		fputc(c, out);
	}
	fclose(inp);
	fclose(out);
	return 0;
}