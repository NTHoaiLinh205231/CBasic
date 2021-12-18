#include <stdio.h>

int main() {
	FILE *inp = fopen("lab1.txt", "rb");
	FILE *out = fopen("lab1-copy.dat", "wb");
	char buff[100];
	int k=0;
	while (!feof(inp)) {
		k+=fread(buff, sizeof(char), 100, inp);
		fwrite(buff, sizeof(char), 100, out);
	}
	printf("Kich thuoc tep: %d bytes\n", k);
	fclose(inp);
	fclose(out);
	return 0;
}