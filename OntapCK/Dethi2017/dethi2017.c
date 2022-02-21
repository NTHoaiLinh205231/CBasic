#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

typedef struct team_s {
	int id;
	char *name;
	int diem;
	int thang;
	int thua;
} *team_t;

typedef struct match_s {
    int x;
    int y;
} *match_t;

#define to_team(t) ((team_t)(((gtype*)t)->v))

void gtype_free_team(gtype v) {
	team_t t = v.v;
	free(t->name);
	free(t);
}

int choice = -1, n;
char *line = NULL;

int menu() {
	printf("\nMenu chuong trinh\n");
	printf("1. In thong tin cac doi bong\n");
	printf("2. In thong tin lich thi dau\n");
	printf("3. Cap nhat ket qua vong dau\n");
	printf("4. Thong ke\n");
	printf("5. Thoat\n");
	printf("Ban muon thuc hien chuc nang nao? [1-5]: ");

	do {
		scanf("%d", &choice);
		if (choice >= 1 && choice <= 5) {
			break;
		} else {
			printf("Hay chon chuc nang [1-5]: ");
		}
	} while (1);
	return choice;
}

team_t get_team(char *line) {
	team_t t = malloc(sizeof(struct team_s));
	t->id = atoi(strtok(line, "\t\n"));
	t->name = strdup(strtok(NULL, "\t\n"));
	t->diem = 0;
	t->thang = 0;
	t->thua = 0;
	return t;
}

match_t get_match(char *line) {
	match_t m = malloc(sizeof(struct match_s));
	m->x = atoi(strtok(line, "\t\n"));
	m->y = atoi(strtok(NULL, "\t\n"));
	return m;
}

void print_result(gsl_t list) {
	printf("%s %15s %10s %15s %15s\n", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
	gsl_traverse(cur, list) {
		team_t t = cur->v;
		printf("%d %15s %10d %15d %15d\n", t->id, t->name, t->diem, t->thang, t->thua);
	}
	printf("\n");
}

void print_match(gvec_t vec, hmap_t map) {
	int idx = 1, count = 0;
	gvec_traverse(cur, vec) {
		if (count % (n/2) == 0) {
			printf("Vong %d\n", idx);
			idx++;
		}
		count++;
		match_t m = cur->v;
		gtype *tmp;
		tmp = hmap_value(map, gtype_l(m->x));
		printf("%s - ", tmp->s);
		tmp = hmap_value(map, gtype_l(m->y));
		printf("%s\n", tmp->s);
	}
}

void update_result(gsl_t list, hmap_t map, gvec_t vec) {
	int idx = 1, count = 0;
	int r1, r2;
	gvec_traverse(cur, vec) {
		if (count % (n/2) == 0) {
			printf("Cap nhat ket qua vong %d\n", idx);
			idx++;
		}
		count++;
		match_t m = cur->v;
		gtype *team1 = hmap_value(map, gtype_l(m->x));
		printf("%s - ", team1->s);
		gtype *team2 = hmap_value(map, gtype_l(m->y));
		printf("%s: ", team2->s);
		scanf("%d - %d", &r1, &r2);
		if (r1 > r2) {
			gsl_traverse(cur, list) {
				team_t tmp = cur->v;
				if (strcmp(team1->s, tmp->name) == 0) {
					tmp->diem += 3;
					tmp->thang += r1;
					tmp->thua += r2;
				}
				if (strcmp(team2->s, tmp->name) == 0) {
					tmp->diem += 0;
					tmp->thang += r2;
					tmp->thua += r1;
				}
			}
		} else if (r1 < r2) {
			gsl_traverse(cur, list) {
				team_t tmp = cur->v;
				if (strcmp(team1->s, tmp->name) == 0) {
					tmp->diem += 0;
					tmp->thang += r1;
					tmp->thua += r2;
				}
				if (strcmp(team2->s, tmp->name) == 0) {
					tmp->diem += 3;
					tmp->thang += r2;
					tmp->thua += r1;
				}
			}
		} else {
			gsl_traverse(cur, list) {
				team_t tmp = cur->v;
				if (strcmp(team1->s, tmp->name) == 0) {
					tmp->diem += 1;
					tmp->thang += r1;
					tmp->thua += r2;
				}
				if (strcmp(team2->s, tmp->name) == 0) {
					tmp->diem += 1;
					tmp->thang += r2;
					tmp->thua += r1;
				}
			}
		}
	}
}

void final(gsl_t list) {
	int min = 10000;
	gsl_t new_list = gsl_create(gtype_free_team);
	gsl_traverse(cur, list) {
		team_t t = cur->v;
		if (t->diem  < min) min = t->diem;
	}
	printf("Cac doi co diem thap nhat la:\n");
	printf("%s %15s %10s %15s %15s\n", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
	gsl_traverse(cur, list){
        team_t t = cur->v;
        if (t->diem == min) {
			printf("%d %15s %10d %15d %15d\n", t->id, t->name, t->diem, t->thang, t->thua);
        } else {
        	gsl_push_back(new_list, gtype_v(t));
        }
    }
	printf("\n");
    printf("Cac doi con lai la\n");
	print_result(new_list);
	gsl_free(new_list);	
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog bongda.txt\n");
		return 1;
	}
	FILE *inp = fopen(argv[1], "r");
	if (!inp) {
		printf("Loi mo tep %s.", argv[1]);
		return 1;
	}

	n = atoi(cgetline(&line, 0, inp));

	team_t t;
	gsl_t list = gsl_create(gtype_free_team);
	hmap_t map = hmap_create(gtype_hash_l, gtype_cmp_l, NULL, NULL);
	for (int i = 0; i < n; ++i)	{
		cgetline(&line, 0, inp);
		t = get_team(line);
		gsl_push_back(list, gtype_v(t));
		hmap_insert(map, gtype_l(t->id), gtype_s(t->name));
	}

	match_t m;
	gvec_t vec = gvec_create(n, NULL);
	for (int i = 0; i < (n - 1)*(n/2 + 1); ++i) {
		cgetline(&line, 0, inp);
		if (!strncmp("Vong", line, 4)) { 
			continue;		
		}
		m = get_match(line);
		gvec_append(vec, gtype_v(m));
	}
	free(line);

	do {
		menu();
		clear_stdin();
	    if (choice == 1) {
	    	print_result(list);
	    } else if (choice == 2) {
	    	print_match(vec, map);
	    } else if (choice == 3) {
	    	update_result(list, map, vec);
	    	print_result(list);
	    } else if (choice == 4) {
	    	final(list);
	    } else {
	    	break;
	    }
	} while(1);
	gsl_free(list);
	hmap_free(map);
	gvec_free(vec);
	fclose(inp);
	return 0;
}