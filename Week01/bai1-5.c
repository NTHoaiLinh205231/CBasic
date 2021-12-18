#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char s[100];
    int i=0;
    printf("Nhap chuoi: ");
    fgets(s, 100, stdin);
    s[strlen(s)-1]='\0';
    while (s[i]!='\0') {
        if (s[i]!=' ' && s[i+1]==' ') printf("%c\n", s[i]);
        else if (s[i]!=' ') printf("%c", s[i]);
        i++;
    }
    return 0;
}
