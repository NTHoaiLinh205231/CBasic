#include <stdio.h>

#define N 1000

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog input.txt\n");
		return 1;
	}
	FILE *inp = fopen(argv[1], "r");
	if (!inp) {
		printf("Loi mo tep.\n");
		return 1;
	}
	char buff[N];
	int i=1;
	while (fgets(buff, N, inp)) {
		printf("%d %s", i, buff);
		i++;
	}
	fclose(inp);
	return 0;
}