#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if ((argc != 2) && (argc != 3)) {
		printf("Usage: ./mycat filename.txt or ./mycat filename.txt -p\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	char buff[100];
	if (argc == 2) {
		while (fgets(buff, 100, f)) {
			printf("%s", buff);
		}
	} else if (strcmp(argv[2], "-p") == 0) {
		int i=0;
		while (fgets(buff, 100, f)) {
			i++;
			printf("%s", buff);
			if (i%10 == 0) {
				getchar();
			}
		}
	} else {
		printf("Usage: ./mycat filename.txt -p\n");
		return 1;
	}
	return 0;
}