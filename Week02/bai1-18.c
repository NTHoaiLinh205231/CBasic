#include <stdio.h>
int main(int argc, char const *argv[])
{
	if (argc != 4) {
		printf("Usage: ./prog tapnguon.txt dodichchuyen tapdich.txt\n");
		return 1;
	}
	FILE *inp = fopen(argv[1], "r");
	if (!inp) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	FILE *out = fopen(argv[3], "w");
	if (!out) {
		printf("Loi mo tep %s.\n", argv[3]);
		return 1;
	}
	int n;
	sscanf(argv[2], "%d", &n);
	int c;
	while ((c=fgetc(inp)) != EOF) {
		fputc(c+n, out);
	}
	fclose(inp);
	fclose(out);
	return 0;
}