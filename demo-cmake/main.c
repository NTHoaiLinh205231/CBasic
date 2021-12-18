#include <stdio.h>
#include "cgen.h"

int main() {
	int a, b;
	hmap_t map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
	hmap_insert(map, gtype_s("hello"), gtype_i(1));
	hmap_insert(map, gtype_s("world"), gtype_i(2));
	gtype *value = hmap_value(map, gtype_s("hello"));
	if (value) {
		printf("Value = %ld\n", value->i);
	} else {
		printf("Key not found! (surprised)\n");
	}
	hmap_free(map);
	return 0;
}