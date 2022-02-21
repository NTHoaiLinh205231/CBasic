#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

typedef struct product_s{
	char *id;
	double price;
} *product_t;

#define to_product1(t) ((product_t)(((gtype*)t)->v))

int gtype_qsort_price1(const void *v1, const void *v2){
    if (to_product1(v2)->price >= to_product1(v1)->price) {
        return 1;
    } else return -1;
}

void cach1(FILE *f){
    int n;
    char *line = NULL;
    cgetline(&line, 0, f);
    n = atoi(line);
    //printf("%d\n", n);
    
    char *id = NULL;
    double price;
    product_t tmp;

    gvec_t p1 = gvec_create(10, gtype_free_v);
    while(cgetline(&line, 0, f)){
        id = strtok(line, " \n");
        price = atof(strtok(NULL, " \n"));
        
        tmp = malloc(sizeof(struct product_s));
        tmp->id = strdup(id);
        tmp->price = price;
        
        gvec_append(p1, gtype_v(tmp));
    }
    free(line);
    /*gvec_traverse(cur, p1){
        tmp = cur->v;
        printf("%s: %.2f\n", tmp->id, tmp->price);
    }
    printf("\n");*/

    gvec_qsort(p1, gtype_qsort_price1);
    printf("Cac san pham co gia cao nhat la:\n");
    double max = 0;
    gvec_traverse(cur, p1) {
        tmp = cur->v;
        if (tmp->price < max) break;
        printf("%s %f\n", tmp->id, tmp->price);
        max = tmp->price;
    }
    free(p1);
    free(tmp);
}

typedef struct product{
    char *id;
    double price;
} *prod_t;

#define to_product2(t) (((gtype*)t)->prod)

int gtype_qsort_price2(const void *v1, const void *v2){
    if (to_product2(v2)->price >= to_product2(v1)->price) {
        return 1;
    } else {
        return -1;
    }
}

void cach2(FILE *f){
    int n;
    char *line = NULL;
    cgetline(&line, 0, f);
    n = atoi(line);

    char *id = NULL;
    double price;
    prod_t tmp;

    gvec_t p2 = gvec_create(10, gtype_free_v);
    while(cgetline(&line, 0, f)){
        id = strtok(line, " \n");
        price = atof(strtok(NULL, " \n"));
        
        tmp = malloc(sizeof(struct product));
        tmp->id = strdup(id);
        tmp->price = price;
        
        gvec_append(p2, gtype_prod(tmp));
    }
    free(line);
    /*gvec_traverse(cur, p2){
        tmp = cur->prod;
        printf("%s: %.2f\n", tmp->id, tmp->price);
    }
    printf("\n");*/

    gvec_qsort(p2, gtype_qsort_price2);
    printf("Cac san pham co gia cao nhat la:\n");
    double max = 0;
    gvec_traverse(cur, p2) {
        tmp = cur->prod;
        if (tmp->price < max) break;
        printf("%s %f\n", tmp->id, tmp->price);
        max = tmp->price;
    }
    free(p2);
    free(tmp);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./prog input.txt c1-hoac-c2\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
    if (!strcmp(argv[2], "c1")) {
        cach1(f);
    } else if (!strcmp(argv[2], "c2")) {
        cach2(f);
    } else {
        printf("Usage: ./prog input.txt c1-hoac-c2\n");
        return 1;
    }
	
    fclose(f);
	return 0;
}