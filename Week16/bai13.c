#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

typedef struct item {
	struct bns_node_g base;
	char *h;
	char *c;
} *item_t;

#define to_item(n) ((item_t)n)
#define to_key_h(n) (to_item(n)->h);
#define to_key_c(c) (to_item(n)->c);

#define to_bns_tree_g(t) ((bns_tree_g_t)(t))
#define bns_tree_g_cmp(t) (to_bns_tree_g(t)->cmp)

sll_node_t sll_create_node_word(const char *word, int number){
  sll_node_t tmp = sll_create_node();
  words nn = realloc(tmp, sizeof(struct words_s));
  nn->w = strdup(word);
  nn->n = number;
  return (sll_node_t) nn;
}

void sll_push_back_word(sll_t list, const char *word, int number) {
  sll_push_back(list, sll_create_node_word(word, number));
}

/*int cmp_id(const void *v1, const void *v2) {
    char *s1 = (*(item_t*)v1)->id_item;
    char *s2 = (*(item_t*)v2)->id_item;
    return strcmp(s1, s2);
}*/

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

	if (strcmp(argv[1], "f1") == 0) {
		printf("f1\n");
	} else if (strcmp(argv[1], "f2") == 0) {
		printf("f2\n");
	} else if (strcmp(argv[1], "f3") == 0) {
		printf("f3\n");
	} else {
		printf("Error!\n");
	}
	fclose(f);
	return 0;
}





/*int find_h(item_t *arr, char const *s, int l, int r){
    if(l <= r) {
        int m = (l + r) / 2;
        if (strcmp(arr[m]->c, s) == 0) { 
        	printf("%s ", arr[m]->h);
        	return m;
        }
        else if(strcmp(arr[m]->c, s) > 0) {
        	return find_h(arr, s, l, m-1);
        } else {
        	return find_h(arr, s, m + 1, r);
        }
    }
    return -1;
}*/

/*int find_c(item_t *arr, char *s, int l, int r){
    
}*/

for (int i = 0; i < idx_n; i++) {
			printf("%d ", arr_n[i]->n);
		}