#include "gvec.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	FILE *f = fopen(argv[1], "r");
	int i = 0;
	char buff[1024];
	gvec_t words = gvec_create(5, NULL);
	while (!feof(f)) {
		fscanf(f, "%s", buff);
		//printf("%s\n", buff);
		gvec_append(words, gtype_s(strdup(buff)));
		i++;
	}
	printf("gvec_traverse: ");
	gvec_traverse(cur, words) {
		printf("%s  ", cur->s);
	}
	printf("\n");

	printf("gvec_size: %ld\n", gvec_size(words));
	printf("gvec_capacity: %ld\n", gvec_capacity(words));
	printf("gvec_arr: %s\n", (*gvec_arr(words)).s); // ???
	printf("gvec_elem: %s\n", gvec_elem(words, 4).s); // ???
	gtype *elem_ptr0 = gvec_arr(words);
	gtype *elem_ptrx = &gvec_elem(words, 4);
	printf("gvec_elem_idx 0: %ld\n", gvec_elem_idx(words, elem_ptr0));
	printf("gvec_elem_idx x: %ld\n", gvec_elem_idx(words, elem_ptrx));
	gvec_remove(words, 4);
	printf("gvec_size after gvec_remove: %ld\n", gvec_size(words));
	gvec_set_capacity(words, 21);
	printf("gvec_capacity after gvec_set_capacity: %ld\n", gvec_capacity(words));
	
	gvec_qsort(words, gtype_qsort_s);
	printf("gvec_traverse after gvec_qsort: ");
	gvec_traverse(cur, words) { // ???
		printf("%s  ", cur->s);
	}
	printf("\n");
	gvec_free(words);
	return 0;
}