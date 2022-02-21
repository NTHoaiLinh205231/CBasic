#include "cgen.h"
#include "ext/io.h"

typedef struct Product{
    char *id;
    double price;
} product;

#define pp(val) ((struct Product*)(((gtype*)val)->v))

int gtype_qsort_product(const void *v1, const void *v2) {
    if (pp(v1)->price < pp(v2)->price) {
        return 1;
    } else return -1;
}

#undef pp

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage ./prog products.txt\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    int n;
    fscanf(f, "%d", &n);

    struct Product *p;
    gvec_t list = gvec_create(0, gtype_free_v);
    for (int i = 0; i < n; i++) {
        char *tmp;
        p = malloc(sizeof(struct Product));
        fscanf(f, "%s %lf", tmp, &p->price);
        p->id = strdup(tmp);
        printf("%s %lf\n", p->id, p->price);
        gvec_append(list, gtype_v(p));
    }

    /* gvec_qsort(list, gtype_qsort_product);
    
    double prev = 0;
    gvec_traverse(cur, list) {
        if (((product*) cur)->price < prev) break;
        printf("%s %lf\n", ((product*) cur)->id, ((product*) cur)->price);
        prev = ((product*) cur)->price;
    }

    gvec_free(list); */
    return 0;
}