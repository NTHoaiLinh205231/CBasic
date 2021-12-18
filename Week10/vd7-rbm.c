#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>

struct word_tf {
	char *word;
	long tf;
};

#define TF(p) (((struct word_tf*)p)->tf)
int word_tf_inc_cmp(const void *p1, const void *p2) {
	return TF(p2) - TF(p1);
}

#define N 10

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog text/lisa_all_text.txt\n");
		return 1;
	}
	FILE *inp = fopen(argv[1], "r");
	char *line = NULL;
	rbm_t words = rbm_create(gtype_cmp_s);
	while (cgetline(&line, 0, inp)) {
		remove_tail_lf(line);
		//printf("%s", line);
		char *tok = strtok(line, " ");
		while (tok) {
			//printf("%s\n", tok);
			//Meo: insert -1 de phan biet nut da co va nut moi
			rbm_node_t n = rbm_insert(words, gtype_s(strdup(tok)), gtype_i(-1));
			if (n->value.i == -1) {
				n->value.i = 1;
			} else {
				n->value.i += 1;
			}
			tok = strtok(NULL, " ");
		}
	}
	fclose(inp);
	free(line);
	long sz = bn_size((bn_tree_t)words);
	printf("So luong tu duy nhat = %ld\n", sz);
	struct word_tf *a = malloc(sizeof(struct word_tf) * sz);
	long idx = 0;
	rbm_traverse(cur, words) {
		//printf("%s - %ld: %ld\n", cur->key.s, strlen(cur->key.s), cur->value.i);
		a[idx].word = cur->key.s;
		a[idx].tf = cur->value.i;
		++idx;
	}
	qsort(a, idx, sizeof(struct word_tf), word_tf_inc_cmp);
	for (long i = 0; i < N; ++i) {
		printf("%s - %ld\n", a[i].word, a[i].tf);
	}
	return 0;
}