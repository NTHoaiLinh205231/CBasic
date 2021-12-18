#include<stdio.h>
#include<time.h>

int main() {
    FILE *fi = fopen("lab1.txt", "r");
    FILE *fo1 = fopen("lab131.txt", "w");
    FILE *fo2 = fopen("lab131.dat", "wb");

    clock_t start_t, end_t;

    start_t = clock();
    int c;
	while ((c = fgetc(fi)) != EOF) {
		fputc(c, fo1);
	}
    end_t = clock();
    printf("fgetc & fputc: %lf\n", (double) end_t - start_t);

    fseek(fi, 0, SEEK_SET);
    start_t = clock();
    char buff1[60];
	while (fgets(buff1, 60, fi)) {
		fputs(buff1, fo1);
	}
    end_t = clock();
    printf("fgets & fputs: %lf\n", (double) end_t - start_t);

    fseek(fi, 0, SEEK_SET);
    start_t = clock();
    char buff2[100];
	while (fread(buff2, sizeof(char), 100, fi)) {
		fwrite(buff2, sizeof(char), 100, fo2);
	}
    end_t = clock();
    printf("fread & fwrite: %lf\n", (double) end_t - start_t);

    fclose(fi);
    fclose(fo1);
    fclose(fo2);
    return 0;
}

// files used: lab1.txt, lab1w.txt and lab1w.dat


/*1.12
#include <stdio.h>

int main() {
	FILE *inp = fopen("lab1.txt", "r");
	FILE *out = fopen("lab1-copy.txt", "w");
	int c;
	while ((c = fgetc(inp)) != EOF) {
		fputc(c, out);
	}
	fclose(inp);
	fclose(out);
}

1.19
#include <stdio.h>
#define N 1000

int main() {
	FILE *inp = fopen("lab1.txt", "r");
	FILE *out = fopen("lab1-copy-1-19.txt", "w");
	char buff[N];
	while (fgets(buff, N, inp)) {
		fputs(buff, out);
	}
	fclose(inp);
	fclose(out);
	return 0;
}

1.29
#include <stdio.h>

int main() {
	FILE *inp = fopen("lab1.txt", "rb");
	FILE *out = fopen("lab1-copy.dat", "wb");
	char buff[100];
	while (fread(buff, sizeof(char), 100, inp)) {
		fwrite(buff, sizeof(char), 100, out);
	}
	fclose(inp);
	fclose(out);
	return 0;
}*/