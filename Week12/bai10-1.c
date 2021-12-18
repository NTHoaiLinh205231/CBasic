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

song *filter(song *list, int n, int ch, int stt[], int idx) {
	song *found = calloc(n, sizeof(song));
	int fo = 0;
	//int f = 0;
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
            		found[fo] = list[i];
            		fo++;
            		stt[t1++] = i;
            	}
            }
            sort(found, fo, ch);
            break;
        case 2: 
            for (int i = 0; i < n; i++) {
            	if (strstr(list[i].s, s) != NULL) {
            		found[fo] = list[i];
            		fo++;
            		stt[t1++] = i;
            	}
            }
            sort(found, fo, ch);
            break;
        case 3: 
            for (int i = 0; i < n; i++) {
            	if (strstr(list[i].m, s) != NULL) {
            		found[fo] = list[i];
            		fo++;
            		stt[t1++] = i;
            	}
            }
            sort(found, fo, ch);
            break;
        case 4: 
        	key = atoi(s);
            for (int i = 0; i < n; i++) {
            	if (list[i].y >= key) {
            		found[fo] = list[i];
            		fo++;
            		stt[t1++] = i;
            	}
            }
            sort(found, fo, 1);
            break;
    }
    if (fo == 0) {
    	printf("Khong tim thay ket qua nao\n");
    } else {
    	//*fo = f;
    	printList(found, fo);
    }
    printf("\n");
    return stt;
}

void add(FILE *f, song *list, int idx) {
	printf("Nhap thong tin cho bai hat:\n");
	char name[1024];
	char singer[1024];
	char musician[1024];
	char year[1024];
	clear_stdin();
	printf("Nhap ten bai hat: ");
	fgets(name, 1024, stdin);
	remove_tail_lf(name);
	printf("Nhap ten ca si: ");
	fgets(singer, 1024, stdin);
	remove_tail_lf(singer);
	printf("Nhap ten nhac si: ");
	fgets(musician, 1024, stdin);
	remove_tail_lf(musician);
	printf("Nhap nam sang tac: ");
	fgets(year, 1024, stdin);
	remove_tail_lf(year);

	list[idx].n = strdup(name);
	list[idx].s = strdup(singer);
	list[idx].m = strdup(musician);
	list[idx].y = atoi(year);

	fprintf(f, "\n%s#*#%s#*#%s#*#%s", name, singer, musician, year);
}

void save(song *list, int idx) {
	FILE *out = fopen("output.txt", "w+");
    for(int i = 0; i < idx; i++) {
		fprintf(out, "%s#*#%s#*#%s#*#%d\n", list[i].n, list[i].s, list[i].m, list[i].y);
    }
    fclose(out);
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
	int idx = 0;

	char *line = NULL;
	char *name;
	char *singer;
	char *musician;
	char *year;
	while (cgetline(&line, 0, f)) {
        if (idx % 1000 == 998) {
        	list = realloc(list,(1000 + idx)*sizeof(song));
        } 
 		remove_tail_lf(line);		
    	//printf("%s\n", line);

		name = strtok(line, "*#*");
       	list[idx].n = strdup(name);
       	//printf("%s\n", a[idx].n);		

		singer = strtok(NULL, "*#*");
		list[idx].s = strdup(singer);
       	//printf("%s\n", a[idx].s);		
		
		musician = strtok(NULL, "*#*");
		list[idx].m = strdup(musician);
       	//printf("%s\n", a[idx].m);		

		year = strtok(NULL, "*#*");
		list[idx].y = atoi(year);
       	//printf("%d\n", a[idx].y);

		idx++;
	}
	free(line);
	
	//song *found = calloc(idx, sizeof(song));
	//int *fo;
	//*fo = 0;
	
	int stt[idx];

	//Lua chon
	for (;;) {
		int ch1 = menu1();
		if (ch1 == 1) {
			int ch2 = menu2();
			sort(list, idx, ch2);
		    printList(list, idx);
		}
		else if (ch1 == 2) {
				int ch2 = menu2();
				filter(list, idx, ch2, stt, idx);
			}
			else if (ch1 == 3) {
					list = realloc(list, (idx+1)*sizeof(song));
					add(f, list, idx);
					idx++;
				}
				else if (ch1 == 4) {
						int ch2 = menu2();
						filter(list, idx, ch2, stt, idx);
						printf("Ban muon xoa bai hat so may?  ");
						int ch3;
						scanf("%d", &ch3);
						clear_stdin();
						printf("Ban thuc su muon xoa toan bo thong tin cua bai hat nay (y/n)?  ");
						char x;
						scanf("%c", &x);
						if (x == 'y') {
							song tmp;
							int del = stt[ch3 - 1];
							printSong(list[del], 1);
							printSong(list[idx - 1], 2);
							tmp = list[idx -1];
							printSong(tmp, 3);
							list[idx - 1] = list[del];
							list[del] = tmp;
							free(list[idx - 1].n);
        					free(list[idx - 1].s);
        					free(list[idx - 1].m);
        					//free(list[idx - 1].y);
        					idx--;
        					printf("Danh sach sau khi xoa: ");
        					printList(list, idx);
        					save(list, idx);
						} else {

							continue;
						}
					}
					else {
						break;
					}
	}
	fclose(f);
	return 0;
}