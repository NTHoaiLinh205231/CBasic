#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

#define LEN 21
#define strequal(s1, s2) (strcmp(s1, s2) == 0)
typedef char id_str[21];

int n;
id_str *items, *suppliers;

void parse_input(const char *fname) {
	FILE *inp = fopen(fname, "r");
	fscanf(inp, "%d", &n);
	items = malloc(n * sizeof(id_str));
	suppliers = malloc(n * sizeof(id_str));
	for (int i = 0; i < n; ++i)	{
		fscanf(inp, "%s %s", items[i], suppliers[i]);
	}
	fclose(inp);
}

void free_input() {
	free(items);
	free(suppliers);
}

void print_gvec(gvec_t vec) {
	gvec_traverse(cur, vec) {
		printf("%s  ", cur->s);
	}
	printf("\n");
}

void func1(const char *id, const char *fname) {
	parse_input(fname);
	gvec_t vec = gvec_create(10, NULL);
	for (int i = 0; i < n; ++i)	{
		if (strequal(id, suppliers[i])) {
			gvec_append(vec, gtype_s(items[i]));
		}
	}
	gvec_qsort(vec, gtype_qsort_s);
	print_gvec(vec);
	gvec_free(vec);
	free_input();
}

void func2(const char *id, const char *fname) {
	parse_input(fname);
	gvec_t vec = gvec_create(10, NULL);
	for (int i = 0; i < n; ++i)	{
		if (strequal(id, items[i])) {
			gvec_append(vec, gtype_s(suppliers[i]));
		}
	}
	gvec_qsort(vec, gtype_qsort_s);
	print_gvec(vec);
	gvec_free(vec);
	free_input();
}

void func3(const char *fname) {
	parse_input(fname);
	hmap_t map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
	for (int i = 0; i < n; ++i) {
		hmap_ires res = hmap_insert(map, gtype_s(items[i]), gtype_l(1));
		if (!res.inserted) {
			++(res.value->l);
		}
	}
	long max = 0;
	const char *maxelement;
	hmap_traverse(key, value, map) {
		if (max < value->l) {
			max = value->l;
			maxelement = key->s;
		}
	}
	printf("%s %ld\n", maxelement, max);
	gvec_t vec = gvec_create(10, NULL);
	for (int i = 0; i < n; ++i)	{
		if (strequal(maxelement, items[i])) {
			gvec_append(vec, gtype_s(suppliers[i]));
		}
	}
	gvec_qsort(vec, gtype_qsort_s);
	print_gvec(vec);
	gvec_free(vec);
	free_input();
	hmap_free(map);
}

int main(int argc, char *argv[]) {
	if (strequal(argv[1], "f1")) {
		func1(argv[2], argv[3]);
	} else if (strequal(argv[1], "f2")) {
		func2(argv[2], argv[3]);
	} else if (strequal(argv[1], "f3")) {
		func3(argv[2]);
	} else {
		printf("Unknown command.\n");
	}
	return 0;
}