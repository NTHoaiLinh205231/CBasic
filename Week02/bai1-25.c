#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		printf("Usage: ./prog tapnguon.txt tapdich.txt\n");
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
	char buff[1024];
	while (fgets(buff, 1024, f1)) {
		fprintf(f2, "%ld %s", strlen(buff)-1, buff);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}