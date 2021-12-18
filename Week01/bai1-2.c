#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    char s[100];
    int max=0;
    int a[256]={0};
    printf("Nhap mot chuoi ky tu: ");
    //fgets(s, 100, stdin);
    scanf("%[^\n]s", s);
    //scanf("%[^\n]%*c",s);
    int n=strlen(s);
    for (int i=0; i<strlen(s); i++) {
        a[s[i]]++;
    }
    for (int i=0; i<strlen(s); i++) {
        if (max<s[i]) max=s[i];
    }
    for (int i=0; i<=max; i++) {
        if (a[i]!=0 && isalpha(i)) {
            printf("%c - %d\n", i, a[i]);
        }
    }
    return 0;
}
/*  char c;
    int a[256]={0};
    while (c=getchar()) {
        if (c=='\n') {
            break;
        }
        ++a[c];
    }
    return 0;
*/
