#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

typedef struct item {
	char *h;
	char *c;
	//int n;
} *item_t;

typedef struct item1 {
	char *h;
	int n;
} *item1_t;

int cmp_h(const void *v1, const void *v2) {
    char *s1 = (*(item_t*)v1)->h;
    char *s2 = (*(item_t*)v2)->h;
    return strcmp(s1, s2);
}

int cmp_c(const void *v1, const void *v2) {
    char *s1 = (*(item_t*)v1)->c;
    char *s2 = (*(item_t*)v2)->c;
    return strcmp(s1, s2);
}

int cmp_n(const void *v1, const void *v2) {
		int t1 = (*(item1_t*)v1)->n;
	  int t2 = (*(item1_t*)v2)->n;
	  return t2 - t1;
}

int main(int argc, char const *argv[]) {
	FILE *f;
	if (argc < 3 || argc > 4) {
		printf("Doc file readme.txt\n");
		return 1;
	} else if (argc == 3) {
		f = fopen(argv[2], "r");
	} else {
		f = fopen(argv[3], "r");
	}
	if (!f) {
		printf("Loi mo tep.\n");
		return 1;
	}

	int num, idx;
	char *line = NULL;
	char *hs, *cs, *ns;

	cgetline(&line, 0, f);
  //printf("%s\n", line);
  num = atoi(line);
 	//printf("%d\n", num);

 	item_t *arr = calloc(num, sizeof(item_t));
 	idx = 0;
	while (cgetline(&line, 0, f)) {
 		remove_tail_lf(line);
    //printf("%s\n", line);
    arr[idx] = malloc(sizeof(struct item));
		hs = strtok(line, " ");
    arr[idx]->h = strdup(hs);
    //printf("%s\n", arr[idx]->h);
    cs = strtok(NULL, " ");
    arr[idx]->c = strdup(cs);
    //printf("%s\n", arr[idx]->c);
		
		idx++;
	}

	item_t *arr_c = calloc(100, sizeof(item_t));

	if (strcmp(argv[1], "f1") == 0) {
		//printf("f1\n");
	  qsort(arr, num, sizeof(arr[0]), cmp_c);
		for (int i = 0; i < num; i++) {
			//printf("%d. %s - %s\n", i, arr[i]->h, arr[i]->c);
			if (strcmp(arr[i]->c, argv[2]) == 0) { 
        	printf("%s ", arr[i]->h);
       }
		}
	  printf("\n");
	} else if (strcmp(argv[1], "f2") == 0) {
		//printf("f2\n");
		item_t *arr_c = calloc(100, sizeof(item_t));
		int idx_c = 0;
		qsort(arr, num, sizeof(arr[0]), cmp_h);
		for (int i = 0; i < num; i++) {
			//printf("%d. %s - %s\n", i, arr[i]->h, arr[i]->c);
			if (strcmp(arr[i]->h, argv[2]) == 0) { 
        if (idx_c % 100 == 99) {
        	arr_c = realloc(arr_c, (100 + idx_c) * sizeof(struct item));
        }
				arr_c[idx_c] = malloc(sizeof(struct item));
				arr_c[idx_c]->h = arr[i]->h;
				arr_c[idx_c]->c = arr[i]->c;
	  		idx_c++;
      }
		}
		qsort(arr_c, idx_c, sizeof(arr_c[0]), cmp_c);
		for (int i = 0; i < idx_c; i++) {
			printf("%s ", arr_c[i]->c);
		}
		printf("\n");
	} else if (strcmp(argv[1], "f3") == 0) {
		printf("f3\n");
		qsort(arr, num, sizeof(arr[0]), cmp_h);
		item1_t *arr_n = calloc(num, sizeof(item_t));
		int idx_n = 0, count = 0;
		for (int i = 0; i < num; i++) {
			for (int j = i + 1; j < num; j++) {
				if (strcmp(arr[i]->h, arr[j]->h) == 0) { 
	  			count++;
     		} else {
     			arr_n[idx_n] = malloc(sizeof(struct item1));
     			arr_n[idx_n]->h = arr[i]->h;
					arr_n[idx_n]->n = count;
					count = 0;
     		}
			}
		}
		
	} else {
		printf("Error!\n");
	}
	fclose(f);
	return 0;
}