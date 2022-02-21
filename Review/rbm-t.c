#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	rbm_t tab = rbm_create(gtype_cmp_s, NULL, NULL);
	rbm_insert(tab, gtype_s("aaa"), gtype_l(100));
	rbm_insert(tab, gtype_s("bbb"), gtype_l(200));
	rbm_insert(tab, gtype_s("ccc"), gtype_l(300));
	rbm_insert(tab, gtype_s("ddd"), gtype_l(400));
	rbm_insert(tab, gtype_s("eee"), gtype_l(500));
	rbm_insert(tab, gtype_s("fff"), gtype_l(600));
	rbm_insert(tab, gtype_s("ggg"), gtype_l(700));
	rbm_insert(tab, gtype_s("hhh"), gtype_l(800));
	rbm_insert(tab, gtype_s("iii"), gtype_l(900));
	rbm_insert(tab, gtype_s("lll"), gtype_l(1000));
	rbm_insert(tab, gtype_s("uuu"), gtype_l(1100));
	printf("rbm_size: %ld\n", rbm_size(tab));
	rbm_traverse(key, value, tab) {
    	printf("%s:%ld\n", key->s, value->l);
  	}

  	printf("Nhap key can tim: ");
	char s[100];
	fscanf(stdin, "%s", s);
	rbm_node_t se;
	if (se = rbm_search(tab, gtype_s(s))) {
	    printf("%s:%ld\n", (se->key).s, (se->value).l);
	} else {
	    printf("Not found!\n");
	}

	printf("Nhap key can tra cuu: ");
	fscanf(stdin, "%s", s);
	gtype *value;
	if (value = rbm_value(tab, gtype_s(s))) {
	    printf("Value of %s: %ld\n", s, value->l);
	} else {
	    printf("Not found!\n");
	}

	rbm_remove(tab, gtype_s(s));
	printf("rbm_size after remove %s: %ld\n", s, rbm_size(tab));
	rbm_traverse(key, value, tab) {
    	printf("%s:%ld\n", key->s, value->l);
  	}
	rbm_free(tab);
	return 0;
}