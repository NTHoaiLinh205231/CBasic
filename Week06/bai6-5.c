#include<stdio.h>
#include "cgen.ic"
#include<string.h>

int exist(bn_tree_t t, char *word) {
	bn_traverse_lnr(cur, t) {
		if (!strcmp(bns_node_g_key(cur).s, word)) return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if ((argc != 2)) {
		printf("Usage: ./prog story.txt\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	int i = 0;
	char word[1000][20];
	int ch;
	while (feof(f) == 0) {
		fscanf(f, "%s", word[i]);
		//printf("%s\n", word[i]);
		i++;
	}
	bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_s);
	for (int j = 0; j < i; j++) {
        if (!exist(t, word[j])) bns_insert_g(t, gtype_s(word[j]));
    }
    printf("So luong tu duy nhat: %ld\n", bn_size(t));
    printf("Cac tu duy nhat: \n");
    bn_traverse_lnr(cur, t) {
        printf("%s  ", bns_node_g_key(cur).s);
  }
  printf("\n");
  bn_free_tree(&t);
	fclose(f);
	return 0;
}