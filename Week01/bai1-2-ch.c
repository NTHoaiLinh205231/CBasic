#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    char c;
    int a[256]={0};
    while (c=getchar()) {
        if (c=='\n') {
            break;
        }
        ++a[c];
    }
    for (int i=0; i<256; i++) {
        if (a[i]!=0 && isalpha(i)) {
            printf("%c - %d\n", i, a[i]);
        }
    }
    return 0;
}
