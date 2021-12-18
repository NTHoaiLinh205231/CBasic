#include <stdio.h>
#include <string.h>
void thaythe(char *str, char c1, char c2)
{
	int i=0;
	while (str[i]!='\0') {
		if (str[i]==c1) str[i]=c2;
		i++;
	}
}
int main()
{
	char str[100], c1, c2;
	printf("Nhap xau ki tu: ");
	fgets(str, 100, stdin);
	str[strlen(str)-1]='\0';
	printf("Nhap hai ki tu: ");
	scanf("%c %c", &c1, &c2);
	thaythe(str, c1, c2);
	printf("Xau sau khi thay ki tu thu nhat bang ki tu thu hai: %s\n", str);
	return 0;
}
