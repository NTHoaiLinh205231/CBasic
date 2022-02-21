#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

typedef struct mark_s {
	char *place;
	int hour;
	int min;
} *mark_t;

void gtype_free_mark(gtype v) {
	mark_t t = v.v;
	free(t->place);
	free(t);
}

int choice = -1;

int menu() {
	printf("\n===================================\n");
	printf("\nCHUONG TRINH TRUY VET COVID19\n");
	printf("1. Nap file log lich su di chuyen\n");
	printf("2. In ra lich su di chuyen\n");
	printf("3. Tim kiem lich su theo dia diem\n");
	printf("4. Tim kiem lich su theo thoi gian\n");
	printf("5. Kiem tra truy vet moi nhat\n");
	printf("6. Thoat\n");
	printf("===================================\n");
	printf("Ban muon thuc hien chuc nang nao? [1-6]: ");

	do {
		scanf("%d", &choice);
		if (choice >= 1 && choice <= 6) {
			break;
		} else {
			printf("Hay chon chuc nang [1-6]: ");
		}
	} while (1);
	return choice;
}

void parse_input(const char *fname, gsl_t list) {
	FILE *inp = fopen(fname, "r");
	if (!inp) {
		printf("Loi mo tep %s.", fname);
		return ;
	}
	char *line = NULL, *place;
	mark_t tmp;
	while (cgetline(&line, 0, inp)) {
		tmp = malloc(sizeof(struct mark_s));
		//printf("Here\n");
		tmp->place = strdup(strtok(line, " \n"));
		tmp->hour = atoi(strtok(NULL, " \n"));
		tmp->min = atoi(strtok(NULL, " \n"));
		printf("%s %d %d\n", tmp->place, tmp->hour, tmp->min);
		gsl_push_back(list, gtype_v(tmp));
	}	
	free(line);
	fclose(inp);
}

void print_history(gsl_t list) {
	printf("%-50s%10s%10s\n", "Dia diem", "Gio", "Phut");
	gsl_traverse(cur, list) {
		mark_t tmp = cur->v;
		printf("%-50s%10d%10d\n", tmp->place, tmp->hour, tmp->min);
	}
}

void search_place(gsl_t list) {
	char *line = NULL;
	printf("Nhap mot dia diem: ");
	cgetline(&line, 0, stdin);
	remove_tail_lf(line);
	int count = 0;
	gsl_traverse(cur, list) {
		mark_t tmp = cur->v;
		if (strcmp(line, tmp->place) == 0) {
			if (count == 0) {
				printf("%d:%d", tmp->hour, tmp->min);
				count++;
			} else {
				printf(", %d:%d", tmp->hour, tmp->min);
			}
		}
	}
	if (count == 0) {
		printf("Ban chua toi dia diem do\n");
	}
	printf("\n");
	free(line);
}

void search_time(gsl_t list) {
	int h, m;
	int count = 0;
	do {
		if (count == 0) {
			printf("Nhap gio va phut (gio phut): ");
		} else {
			printf("Du lieu khong hop le. Nhap lai: ");
		}
		scanf("%d %d", &h, &m);
		if (h >= 0 && h <= 24 && m >= 0 && m <= 60) {
			count++;
			break;
		}
	} while (h < 0 && h > 24 && m < 0 && m > 60);
	count = 0;

	gsl_traverse(cur, list) {
		mark_t tmp = cur->v;
		if (cur != gsl_back(list)) {
			mark_t tmp_next = gsn_next(cur)->v;
			//printf("%d:%d\n", tmp->hour, tmp->min);
			//printf("%d:%d\n", tmp_next->hour, tmp_next->min);
			if (tmp->hour < tmp_next->hour) {
				if (h > tmp->hour && h < tmp_next->hour) {
					printf("%s\n", tmp->place);
					count++;
				}
			} else {
				if (h == tmp->hour) {
					if (m >= tmp->min && m <= tmp_next->min) {
						printf("%s\n", tmp->place);
						count++;
					}
				}
			}
		} else {
			if (h >= tmp->hour && m >= tmp->min) {
				printf("%s\n", tmp->place);
				count++;
			}
		}	
	}
	if (count == 0) {
		printf("Khong tim thay lich su di chuyen\n");
	}
	printf("\n");
}

void check(gsl_t list) {
	int h, m;
	int x = 0, y = 0, z = 0;
	int count = 0;
	char *line = NULL;
	printf("Nhap dia diem: ");
	cgetline(&line, 0, stdin);
	remove_tail_lf(line);
	do {
		if (count == 0) {
			printf("Nhap gio va phut (gio phut): ");
		} else {
			printf("Du lieu khong hop le. Nhap lai: ");
		}
		scanf("%d %d", &h, &m);
		if (h >= 0 && h <= 24 && m >= 0 && m <= 60) {
			count++;
			break;
		}
	} while (h < 0 && h > 24 && m < 0 && m > 60);
	count = 0;
	gsl_traverse(cur, list) {
		mark_t tmp = cur->v;
		if (strcmp(line, tmp->place) == 0) {
			count++;
		}
	}
	if (count == 0) {
		printf("Lich su di chuyen cua ban OK\n");
		return ;
	}

	/*gsl_traverse(cur, list) {
		mark_t tmp = cur->v;
		if (tmp->hour )
	}*/
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog log.txt\n");
		return 1;
	}
	gsl_t list = gsl_create(gtype_free_mark);
	do {
		menu();
		clear_stdin();
	    if (choice == 1) {
	    	parse_input(argv[1], list);
	    } else if (choice == 2) {
	    	print_history(list);
	    } else if (choice == 3) {
	    	search_place(list);
	    } else if (choice == 4) {
	    	search_time(list);
	    } else if (choice == 5) {
	    	check(list);
	    } else {
	    	break;
	    }
	} while(1);

	gsl_free(list);
	return 0;
}