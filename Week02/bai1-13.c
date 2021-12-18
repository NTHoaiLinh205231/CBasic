#include <stdio.h>
#include <ctype.h>

int main() {
	FILE *inp = fopen("lab1.txt", "r");
	FILE *out = fopen("lab1-hoa-thuong.txt", "w");
	int c;
	while ((c = fgetc(inp)) != EOF) {
		if (isalpha(c)) {
			if (c >= 'A' && c <='Z') fputc(tolower(c), out);
			else fputc(toupper(c), out);
		} else fputc(c, out);
	}
	return 0;
}