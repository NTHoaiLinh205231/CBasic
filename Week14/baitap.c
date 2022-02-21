#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

typedef struct item{
	char *id;
	char *name;
	double price;
	int number;
} item;

int menu() {
	int ch;
	do {
		printf("\nChon chuc nang:\n");
		printf("1. Xem thong tin mat hang\n");
		printf("2. Tao đon hang\n");
		printf("3. Thoat\n");
		printf("Lua chon cua ban la [1, 2, 3]?  ");
		scanf("%d", &ch);
    } while(ch < 1 || ch > 3);
	return ch;
}

void printList(item *list, int n){
	printf("     %-10s %-30s %15s %20s\n", "Ma so", "Ten mat hang", "Gia tien", "So luong trong kho");
    for(int i = 0; i < n; i++) {
    	printf("%-3d  %-10s %-30s %15g %15d\n", i+1, list[i].id, list[i].name, list[i].price, list[i].number);
    }
    printf("\n");
}

int check_id(item *list, int n, char *id1) {
	for (int i = 0; i < n; i++) {
		if (!strcmp(list[i].id, id1)) {
			return i;
		}
	}
	return -1;
}

int check_number(int choice, int k) {
	if (k <= choice) return 1;
	else return 0;
}

void *func2(item *list, item *order, int n, int *n1) {
	char *id1 = NULL;
	char *name1;
	double price1;
	int number1;
	clear_stdin();
	for (;;) {
		printf("Nhap ma so mat hang (Nhap STOP de ket thuc): ");
		cgetline(&id1, 0, stdin);
 		remove_tail_lf(id1);
 		if (!strcmp("STOP", id1)) {
 			break;
 		}
		int choice = check_id(list, n, id1);
		if (choice != -1) {
			printf("Nhap so luong: ");
			scanf("%d", &number1);
			clear_stdin();
			if (check_number(list[choice].number, number1)) {
				order[*n1].id = list[choice].id;
				order[*n1].name = list[choice].name;
				order[*n1].price = list[choice].price;
				order[*n1].number = number1;				
		       	//printf("%s\n", order[*n1].id);
		       	//printf("%s\n", order[*n1].name);
		       	//printf("%g\n", order[*n1].price);
		       	//printf("%d\n", order[*n1].number);
				(*n1)++;

			} else {
				printf("Khong co du so luong yeu cau.\n");
			}
		} else {
			printf("Khong co mat hang ban muon chon.\n");
		}
	}
	printf("Cong ty ABC\n");
	printf("Don hang ban le\n");
	double sum = 0;
	printf("     %-10s %-30s %15s %20s %20s\n", "Ma so", "Ten mat hang", "Gia tien", "So luong trong kho", "Thanh tien");
    for(int i = 0; i < *n1; i++) {
    	printf("%-3d  %-10s %-30s %15g %15d %25.0lf\n", i+1, order[i].id, order[i].name, order[i].price, order[i].number, order[i].price * order[i].number);
		sum += order[i].price * order[i].number;
    }
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("%96s %.0lf\n", "Tong tien:", sum);
}

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog inp.txt\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	
	int n;
	char *line = NULL;
	cgetline(&line, 0, f);
   	//printf("%s\n", line);
    n = atoi(line);
   	//printf("%d\n", n);

 	item *list = malloc(n * sizeof(item));
	char *id;
	char *name;
	char *price;
	char *number;
	int idx = 0;
	while (cgetline(&line, 0, f)) {
        if (n % 1000 == 999) {
        	list = realloc(list,(1000 + n)*sizeof(item));
        }
 		remove_tail_lf(line);
    	//printf("%s\n", line);

		id = strtok(line, " ");
       	list[idx].id = strdup(id);
       	//printf("%s\n", list[idx].id);

		name = strtok(NULL, " ");
		list[idx].name = strdup(name);
       	//printf("%s\n", list[idx].name);

		price = strtok(NULL, " ");
		sscanf(price, "%lf", &list[idx].price);
       	//printf("%g\n", list[idx].price);

		number = strtok(NULL, " ");
		list[idx].number = atoi(number);
       	//printf("%d\n", list[idx].number);

		idx++;
	}
	free(line);
	
	
	for (;;) {
		int ch = menu();
		if (ch == 1) {
			printList(list, n);
		}
		else if (ch == 2) {
				item *order = malloc(n * sizeof(item));
				int *n1;
				*n1 = 0;
				func2(list, order, n, n1);
			}
			else {
				break;
			}
	}
	for(int i = 0; i < n; i++) {
        free(list[i].id);
        free(list[i].name);
    }
    free(list);
	fclose(f);
	return 0;
}