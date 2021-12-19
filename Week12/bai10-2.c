#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

typedef struct song{
	char *n;
	char *s;
	char *m;
	int y;
} song;

int menu1() {
	int ch;
	do {
		printf("\nChọn chức năng:\n");
		printf("1. Xem danh sách bài hát\n");
		printf("2. Lọc danh sách bài hát\n");
		printf("3. Thêm bài hát\n");
		printf("4. Xoá bài hát\n");
		printf("5. Thoát\n");
		printf("Lựa chọn của bạn là [1, 2, 3, 4, 5]?  ");
		scanf("%d", &ch);
    } while(ch < 1 || ch > 5);
	return ch;
}

int menu2() {
	int ch;
	do {
		printf("\nLọc danh sách bài hát theo:\n");
		printf("1. Tên bài hát\n");
		printf("2. Ca sĩ\n");
		printf("3. Nhạc sĩ\n");
		printf("4. Năm sáng tác\n");
		printf("Lựa chọn của bạn là [1, 2, 3, 4]?  ");
		scanf("%d", &ch);
    } while(ch < 1 || ch > 4);
	return ch;
}

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

void printSong(song a, int i) {
    printf("%-3d  %-60s %-20s %-20s %-5d\n", i, a.n, a.s, a.m, a.y);
}

void printList(song *list, int n){
	printf("     %-60s %-20s %-20s %-5s\n", "Tên bài hát", "Ca sĩ", "Nhạc sĩ", "Năm");
    for(int i = 0; i < n; i++) {
        printSong(list[i], i+1);
    }
    printf("\n");
}

int *filter(song *list, int n, int ch) {
	song *found = calloc(n, sizeof(song));
	int fo = 0;
	int *pos = malloc(n * sizeof(int));
	int t1 = 0;
	char s[1024];
	clear_stdin();
	printf("Nhập cụm từ tìm kiếm: ");
	fgets(s, 1024, stdin);
	remove_tail_lf(s);
	int key;
	switch(ch) {
        case 1: 
            for (int i = 0; i < n; i++) {
            	if (strstr(list[i].n, s) != NULL) {
            		found[fo++] = list[i];
            		pos[t1++] = i;
            	}
            }
            sort(found, fo, ch);
            break;
        case 2: 
            for (int i = 0; i < n; i++) {
            	if (strstr(list[i].s, s) != NULL) {
            		found[fo++] = list[i];
            		pos[t1++] = i;
            	}
            }
            sort(found, fo, ch);
            break;
        case 3: 
            for (int i = 0; i < n; i++) {
            	if (strstr(list[i].m, s) != NULL) {
            		found[fo++] = list[i];
            		pos[t1++] = i;
            	}
            }
            sort(found, fo, ch);
            break;
        case 4: 
        	key = atoi(s);
            for (int i = 0; i < n; i++) {
            	if (list[i].y >= key) {
            		found[fo++] = list[i];
            		pos[t1++] = i;
            	}
            }
            sort(found, fo, 1);
            break;
    }
    if (fo == 0) {
    	printf("Không tìm thấy kết quả nào\n");
    } else {
    	printList(found, fo);
    }
    return pos;
}

void add(song *list, int num, const char *filename) {
	printf("Nhập thông tin cho bài hát:\n");
	char name[1024];
	char singer[1024];
	char musician[1024];
	int year;
	clear_stdin();
	printf("Nhập tên bài hát: ");
	fgets(name, 1024, stdin);
	remove_tail_lf(name);
	printf("Nhập tên ca sĩ: ");
	fgets(singer, 1024, stdin);
	remove_tail_lf(singer);
	printf("Nhập tên nhạc sĩ: ");
	fgets(musician, 1024, stdin);
	remove_tail_lf(musician);
	printf("Nhập năm sáng tác: ");
	scanf("%d", &year);

	list[num - 1].n = strdup(name);
	list[num - 1].s = strdup(singer);
	list[num - 1].m = strdup(musician);
	list[num - 1].y = year;

	FILE *f1 = fopen(filename, "a");
    fprintf(f1,"\n%s*#*%s*#*%s*#*%d", list[num-1].n, list[num-1].s, list[num-1].m, list[num-1].y);
    fclose(f1);
}

int delete(song *list, int *num, const char *filename) {
	int ch2 = menu2();
	int *pos = filter(list, *num, ch2);
	printf("Ban muon xoa bai hat so may?  ");
	int del;
	scanf("%d", &del);
	clear_stdin();
	printf("Ban thuc su muon xoa toan bo thong tin cua bai hat nay (y/n)?  ");
	char x;
	scanf("%c", &x);
	if (x == 'y') {
		del = pos[del -1];
		free(list[del].n);
    	free(list[del].s);
    	free(list[del].m);
		list[del] = list[*num - 1];
    	(*num)--;
    } else {
    	printf("Khong xoa bai hat nua\n");
    	return 0;
    }
    free(pos);

    FILE *out = fopen(filename, "w");
    for(int i = 0; i < *num; i++) {
    	//printf("%d\n", i);
		if (i == 0) {
			fprintf(out, "%s#*#%s#*#%s#*#%d", list[i].n, list[i].s, list[i].m, list[i].y);
		}
		fprintf(out, "\n%s#*#%s#*#%s#*#%d", list[i].n, list[i].s, list[i].m, list[i].y);
    }
    fclose(out);
    return del;
}

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog inp.txt\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r+");
	if (!f) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	
	//Đọc dữ liệu
 	song *list = malloc(1000 * sizeof(song));
	int num = 0;

	char *line = NULL;
	char *name;
	char *singer;
	char *musician;
	char *year;
	while (cgetline(&line, 0, f)) {
        if (num % 1000 == 999) {
        	list = realloc(list,(1000 + num)*sizeof(song));
        } 
 		remove_tail_lf(line);		
    	//printf("%s\n", line);

		name = strtok(line, "*#*");
       	list[num].n = strdup(name);
       	//printf("%s\n", a[num].n);		

		singer = strtok(NULL, "*#*");
		list[num].s = strdup(singer);
       	//printf("%s\n", a[num].s);		
		
		musician = strtok(NULL, "*#*");
		list[num].m = strdup(musician);
       	//printf("%s\n", a[num].m);		

		year = strtok(NULL, "*#*");
		list[num].y = atoi(year);
       	//printf("%d\n", a[num].y);

		num++;
	}
	free(line);
	
	//Lua chon
	for (;;) {
		int ch1 = menu1();
		if (ch1 == 1) {
			int ch2 = menu2();
			sort(list, num, ch2);
		    printList(list, num);
		}
		else if (ch1 == 2) {
				int ch2 = menu2();
				filter(list, num, ch2);
			}
			else if (ch1 == 3) {
					num++;
					list = realloc(list, num*sizeof(song));
					add(list, num, argv[1]);
				}
				else if (ch1 == 4) {
						delete(list, &num, argv[1]);
					}
					else {
						break;
					}
	}
	fclose(f);
	return 0;
}
/*
Bài hát số 1#*#NVA#*#NSZ#*#1990
Bài hát số 2#*#NVB#*#NSY#*#1980
Bài hát số 3#*#NVC#*#NSX#*#1998
Bài ca không tên 1#*#TVC#*#STA#*#2000
Bài ca không tên 2#*#TVD#*#STB#*#2002
Bài ca không tên 3#*#TVE#*#STC#*#2020
*/