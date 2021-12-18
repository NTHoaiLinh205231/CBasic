#include <stdio.h>
int main(int argc, char const *argv[])
{
	if (argc != 3) {
		printf("Usage: ./prog input.txt output.txt\n");
		return 1;
	}
	FILE *inp = fopen(argv[1], "r");
	if (!inp) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	FILE *out = fopen(argv[2], "w");
	if (!out) {
		printf("Loi mo tep %s.\n", argv[2]);
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