#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: ./prog filename.txt\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "a+");
	if (!f) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	char buff[100], c[80];
	int i=0;
	while (fgets(buff, 100, f)) {
		c[i]=buff[0];
		i++;
	}
	fputc('\n', f);
	for (int j=0; j<i; j++) {
		fputc(c[j], f);
	}
	return 0;
}