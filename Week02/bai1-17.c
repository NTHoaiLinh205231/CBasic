#include <stdio.h>

int main(int argc, char * argv[]) {
	if (argc != 3) {
		printf("Usage: ./double_line tap1.txt tap2.txt\n");
		return 1;
	}
	FILE *f1 = fopen(argv[1], "r");
	if (!f1) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	FILE *f2 = fopen(argv[2], "w");
	if (!f2) {
		printf("Loi mo tep %s.\n", argv[2]);
		return 1;
	}
	int c;
	while ((c=fgetc(f1)) != EOF) {
		if (c == '\n') {
			fputc(c, f2);
		}
		fputc(c, f2);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}