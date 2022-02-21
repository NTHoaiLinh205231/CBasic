#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hang_s {
	int id;
	char *toy;
} *hang_t;

int choice = 0;
char *line = NULL;
int id;
char *toy;

int menu() {
	printf("\nMenu chuong trinh\n");
	printf("1. Doc file A\n");
	printf("2. Doc file B\n");
	printf("3. Tim kiem\n");
	printf("4. Tong hop\n");
	printf("5. Thong ke\n");
	printf("6. Thoat\n");
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

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./prog A.txt B.txt\n");
		return 1;
	}

	rbm_t tr = rbm_create(gtype_cmp_l, NULL, gtype_free_s);
	hang_t *arr = malloc(100 * sizeof(hang_t));
	int nb = 0;
	rbm_t tr_toy = rbm_create(gtype_cmp_s, gtype_free_s, NULL);

	do {
		menu();
	    if (choice == 1) {
	        FILE *f1 = fopen(argv[1], "r");
			if (!f1) {
				printf("Loi mo tep %s.\n", argv[1]);
				return 1;
			}

			clear_stdin();
			while(cgetline(&line, 0, f1)) {
				id = atoi(strtok(line, "\t\n"));
				toy = strtok(NULL, " \t\n");
				if (toy == NULL) {
					printf("Khong co thong tin do choi cua %d. Hay nhap them: ", id);
					cgetline(&toy, 0, stdin);
					remove_tail_lf(toy);			
				}
				rbm_insert(tr, gtype_l(id), gtype_s(strdup(toy)));
			}
			
			printf("Ma so - Do choi\n");
			rbm_traverse(key, value, tr) {
				printf("%ld - %s\n", key->l, value->s);
			}
			printf("\n");
			fclose(f1);
	    } else if (choice == 2) {
	        FILE *f2 = fopen(argv[2], "r");
			if (!f2) {
				printf("Loi mo tep %s.\n", argv[2]);
				return 1;
			}
			
			clear_stdin();
			while (cgetline(&line, 0, f2)) {
		        if (nb % 100 == 99) {
		        	arr = realloc(arr,(100 + nb)*sizeof(hang_t));
		        }
		    	//printf("%s\n", line);

				id = atoi(strtok(line, " \t\n"));
				toy = strtok(NULL, "\t\n");
				if (toy == NULL) {
					printf("Khong co thong tin do choi cua %d. Hay nhap them: ", id);
					cgetline(&toy, 0, stdin);
					remove_tail_lf(toy);			
				}
				arr[nb] = malloc(sizeof(struct hang_s));
		       	arr[nb]->id = id;
				arr[nb]->toy = strdup(toy);
				//printf("%d - %s\n", arr[nb]->id, arr[nb]->toy);
				nb++;
			}
			
			printf("Ma so - Do choi\n");
			for(int i = 0; i < nb; ++i) {
				printf("%d - %s\n", arr[i]->id, arr[i]->toy);
			}
			printf("\n");
			fclose(f2);
	    } else if (choice == 3) {
	    	for(int i = 0; i < nb; ++i) {
	    		if (rbm_remove(tr, gtype_l(arr[i]->id))) {
	    			printf("Da xoa thong tin bi trung: %d - %s\n", arr[i]->id, arr[i]->toy);
	    		}
			}
			printf("Thong tin o cay A sau khi xoa:\n");
			printf("Ma so - Do choi\n");
			rbm_traverse(key, value, tr) {
				printf("%ld - %s\n", key->l, value->s);
			}
	    } else if (choice == 4) {
	        for(int i = 0; i < nb; ++i) {
	    		rbm_insert(tr, gtype_l(arr[i]->id), gtype_s(arr[i]->toy));
			}
			bn_tree_t t = (bn_tree_t)tr;
			rbm_node_t tmp;
			bn_traverse_rnl(cur, t) {
				tmp = (rbm_node_t) cur;
				printf("%ld - %s\n", (tmp->key).l, (tmp->value).s);
			}
	    } else if (choice == 5) {
	    	rbm_traverse(key, value, tr) {	
	    		rbm_ires res = rbm_insert(tr_toy, gtype_s(value->s), gtype_l(1));	
	    		if (!res.inserted) {
	    			res.value->l++;
	    		}
	    	}
	    	printf("Loai do choi: so luong\n");
	    	rbm_traverse(key, value, tr_toy) {
	    		printf("%s: %ld\n", key->s, value->l);
	    	}
	    } else {
	    	break;
	    }
	} while(1);
	rbm_free(tr);
	free(line);	
	return 0;
}