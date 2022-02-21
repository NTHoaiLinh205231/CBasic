#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct order_s {
	char *id;
	int total;
} *order_t;

#define to_order(t) ((order_t)(((gtype*)t)->v))

/*int gtype_qsort_order(const void *v1, const void *v2){
  	return to_order(v2)->total - to_order(v1)->total;
}*/

int cmp_order(const void *v1, const void *v2) {
	return to_order(v2)->total - to_order(v1)->total;
}

int parse_input_products(const char *inp_name, hmap_t out) {
 	FILE *inp = fopen(inp_name, "r");
  	if (!inp) {
		printf("Loi mo tep %s.\n", inp_name);
		return 1;
	}
	char *s = NULL;
	char *id = NULL;
	int price;
	cgetline(&s, 0, inp);
	int n = 0;
	sscanf(s, "%d", &n);
	for (int i = 0; i < n; ++i) {
		cgetline(&s, 0, inp);
		id = strdup(strtok(s, " \n"));
	  	price = atoi(strtok(NULL, " \n"));
	    //printf("%s %d\n", id ,price);
	    hmap_insert(out, gtype_s(id), gtype_l(price)); 
	}
	free(s);
	free(id);
	fclose(inp);
	return 0;
}

int main(int argc, const char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./prog products.txt orders.txt\n");
		return 1;
	}

	hmap_t products = hmap_create(gtype_hash_s, gtype_cmp_s, gtype_free_s, NULL);
	parse_input_products(argv[1], products);
	FILE *f = fopen(argv[2], "r");
  	if (!f) {
		printf("Loi mo tep %s.\n", argv[2]);
		return 1;
	}
	
	int n, ni, quantity;
	char *line = NULL;
	char *id = NULL;

	cgetline(&line, 0, f);
	sscanf(line, "%d", &n);
	//gvec_t orders = gvec_create(n, gtype_free_v);
	//order_t tmp = malloc(sizeof(struct order_s));
	order_t *list_order = malloc(n * sizeof(order_t));
	int price;
	for (int i = 0; i < n; ++i) {
		list_order[i] = malloc(sizeof(struct order_s));
		cgetline(&line, 0, f);
		//tmp->id = strdup(strtok(line, " \n"));
		//tmp->total = 0;
		id = strtok(line, " \n");
		ni = atoi(strtok(NULL, " \n"));
		price = 0;
		for (int j = 0; j < ni; ++j) {
			gtype *v = hmap_value(products, gtype_s(strtok(NULL, " \n")));
	  		quantity = atoi(strtok(NULL, " \n"));
	  		//tmp->total += quantity * v->l;
	  		price += quantity * v->l;
		}
		//gvec_append(orders, gtype_v(tmp));
		list_order[i]->id = strdup(id);
		list_order[i]->total = price;
	}
	//gvec_qsort(orders, gtype_qsort_order);
	qsort(list_order, n, sizeof(list_order), cmp_order);
	/*int count = 0;
	gvec_traverse(cur, orders) {
		tmp = cur->v;
		printf("%s %d\n", tmp->id, tmp->total);
		count++;
		if (count == 3) break;
	}*/
	for (int i = 0; i < 3; ++i) {
		printf("%s %d\n", list_order[i]->id, list_order[i]->total);
	}
	free(line);
	//free(tmp);
	//gvec_free(orders);
	hmap_free(products);
	fclose(f);
	return 0;
}