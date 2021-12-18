#include <stdio.h>

int main() {
	FILE *inp = fopen("lab1-copy.dat", "rb");
	char buff[100];
	while (fread(buff, sizeof(char), 100, inp)) {
		printf("%s", buff);
	}
	fclose(inp);
}