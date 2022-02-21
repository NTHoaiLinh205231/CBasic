#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cgen.h"
#include "ext/io.h"

typedef struct item {
	char *id_item;
	int price;
} *item_t;

typedef struct item1 {
	char *id_item1;
	int n;
} *item1_t;

typedef struct order {
	char *id_order;
	int number;
	item1_t *list_order;
	int total;
} *order_t;

int cmp_id(const void *v1, const void *v2) {
    char *s1 = (*(item_t*)v1)->id_item;
    char *s2 = (*(item_t*)v2)->id_item;
    return strcmp(s1, s2);
}

int cmp_total(const void *v1, const void *v2) {
	int t1 = (*(order_t*)v1)->total;
    int t2 = (*(order_t*)v2)->total;
    return t2 - t1;
}

int findprice(item_t *products, char *s, int l, int r){
    if(l <= r){
        int m = (l + r) / 2;
        if (strcmp(products[m]->id_item, s) == 0) return products[m]->price;
        else if(strcmp(products[m]->id_item, s) > 0) return findprice(products, s, l, m-1);
        else return findprice(products, s, m + 1, r);
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    clock_t start = clock();
	if (argc != 3) {
		printf("Usage: ./prog input1.txt input2.txt\n");
		return 1;
	}
	FILE *f1 = fopen(argv[1], "r");
	FILE *f2 = fopen(argv[2], "r");
	if (!f1) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	if (!f2) {
		printf("Loi mo tep %s.\n", argv[2]);
		return 1;
	}

	int np, no, idx;
	char *line = NULL;
	char *id, *price, *number;

	cgetline(&line, 0, f1);
   	//printf("%s\n", line);
    np = atoi(line);
   	//printf("%d\n", np);

 	item_t *products = calloc(np, sizeof(item_t));
 	idx = 0;
	while (cgetline(&line, 0, f1)) {
 		remove_tail_lf(line);
    	//printf("%s\n", line);

    	products[idx] = malloc(sizeof(struct item));
		id = strtok(line, " ");
       	products[idx]->id_item = strdup(id);
       	//printf("%s\n", products[idx]->id_item);

		price = strtok(NULL, " ");
		products[idx]->price = atoi(price);
       	//printf("%d\n", products[idx]->price);

		idx++;
	}
	//printf("quicksort\n");
    qsort(products, np, sizeof(products[0]), cmp_id);
	//printf("quicksort\n");

	cgetline(&line, 0, f2);
   	//printf("%s\n", line);
    no = atoi(line);
   	//printf("%d\n", no);

 	order_t *orders = calloc(no, sizeof(order_t));
 	idx = 0;
	while (cgetline(&line, 0, f2)) {
 		remove_tail_lf(line);
    	//printf("%s\n", line);

    	orders[idx] = malloc(sizeof(struct order));
		id = strtok(line, " ");
       	orders[idx]->id_order = strdup(id);
       	//printf("%s\n", orders[idx]->id_order);

		number = strtok(NULL, " ");
		orders[idx]->number = atoi(number);
       	//printf("%d\n", orders[idx]->number);

        orders[idx]->list_order = calloc(orders[idx]->number, sizeof(item1_t));
        orders[idx]->total = 0;
        for (int i = 0; i < orders[idx]->number; i++) {
        	orders[idx]->list_order[i] = malloc(sizeof(struct item1));
            id = strtok(NULL, " ");
            orders[idx]->list_order[i]->id_item1 = strdup(id);
            //printf("%d - %s - ", i+1, orders[idx]->list_order[i]->id_item1);
            number = strtok(NULL, " ");
            orders[idx]->list_order[i]->n = atoi(number);
            //printf("%d\n", orders[idx]->list_order[i]->n);
        }
		idx++;
	}
    free(line);
	fclose(f1);
	fclose(f2);

	for(int i = 0; i < no; i++) {
        for(int j = 0; j < orders[i]->number; j++){
            orders[i]->total += findprice(products, orders[i]->list_order[j]->id_item1, 0, np-1) * (orders[i]->list_order[j]->n);
        }
        //printf("%s: %d\n", orders[i]->id_order, orders[i]->total);
    }
    qsort(orders, no, sizeof(orders[0]), cmp_total);
    for(int i = 0; i < 3; i++) {
        printf("%s %d\n", orders[i]->id_order, orders[i]->total);
    }
    for(int i = 0; i < np; i++) {
    	free(products[i]->id_item);
    }
    free(products);
    for(int i = 0; i < no; i++) {
    	free(orders[i]->id_order);
    	for(int j = 0; j < orders[i]->number; j++) {
    		free(orders[i]->list_order[j]->id_item1);
    	}
    }
    free(orders);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Thoi gian chay: %lf\n", cpu_time_used);
	return 0;
}