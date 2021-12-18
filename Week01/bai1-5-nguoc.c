//In cac tu trong mot cau theo thu tu nguoc lai
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char s[100];
    scanf("%[^\n]%*c", s);
    //printf("%s\n", s);
    int len=strlen(s);
    for (int i=0; i<len; ++i) {
        if (!isalpha(s[i])) {
            s[i]='\0';
        }
    }
    char *words[100];
    int idx=0;
    for (int i=0; i<len; ++i) {
        if (isalpha(s[i])) {
            words[idx++]=s+i;
            //printf("%s\n", s+i);
            i+=strlen(s+i);
        }
    }
    for (int i=idx-1; i>=0; --i) {
        printf("%s\n", words[i]);
    }
    return 0;
}