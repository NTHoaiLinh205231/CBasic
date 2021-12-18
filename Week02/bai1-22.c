#include <stdio.h>
#include <string.h>

#define N 5

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Usage: ./prog tep1.txt tep2.txt tep3.txt\n");
		return 1;
	}
	FILE *f1 = fopen(argv[1], "r");
	if (!f1) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	FILE *f2 = fopen(argv[2], "r");
	if (!f2) {
		printf("Loi mo tep %s.\n", argv[2]);
		return 1;
	}
	FILE *f3 = fopen(argv[3], "w");
	if (!f3) {
		printf("Loi mo tep %s.\n", argv[3]);
		return 1;
	}
	char buff[N];
	int check1=1, check2=1;
	while ((!feof(f1)) || (!feof(f2))) {
		if ( check1) {
			if (fgets(buff, N, f1) != NULL) {
				fputs(buff, f3);
				if (buff[strlen(buff)-1] == '\n') check2=1;
				else check2=0;
			}
		}
		if (check2) {
			if (fgets(buff, N, f2) != NULL) {
				fputs(buff, f3);
				if (buff[strlen(buff)-1] == '\n') check1=1;
				else check1=0;
			}
		}
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);
	return 0;
}