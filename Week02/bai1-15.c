#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./prog tep1.txt tep2.txt\n");
		return 1;
	}
	FILE *f1 = fopen(argv[1], "a");
	if (!f1) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	FILE *f2 = fopen(argv[2], "r");
	if (!f2) {
		printf("Loi mo tep %s.\n", argv[2]);
		return 1;
	}
	int c;
	while ((c=fgetc(f2)) != EOF) {
		fputc(c, f1);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}