#include <stdlib.h>

typedef struct song{
	char *n;
	char *s;
	char *m;
	int y;
} song;

int cmp_name(const void *v1, const void *v2){
    char *s1 = (*(song*)v1).n;
    char *s2 = (*(song*)v2).n;
    return strcmp(s1,s2);
}

int cmp_singer(const void *v1, const void *v2){
    char *s1 = (*(song*)v1).s;
    char *s2 = (*(song*)v2).s;
    return strcmp(s1,s2 );
}

int cmp_musician(const void *v1, const void *v2){
    char *s1 = (*(song*)v1).m;
    char *s2 = (*(song*)v2).m;
    return strcmp(s1,s2 );
}

int cmp_year(const void *v1, const void *v2){
    int i1 = (*(song*)v1).y;
    int i2 = (*(song*)v2).y;
    return i1 - i2;
}

void sort(song *list, int n, int ch){
    switch(ch) {
        case 1: 
            qsort(list,n, sizeof(song), cmp_name);
            break;
        case 2: 
            qsort(list,n, sizeof(song), cmp_singer);
            break;
        case 3: 
            qsort(list,n, sizeof(song), cmp_musician);
            break;
        case 4: 
            qsort(list,n, sizeof(song), cmp_year);
            break;
    }
}