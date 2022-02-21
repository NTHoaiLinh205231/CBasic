#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog collection.txt\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Loi mo tep %s.\n", argv[1]);
		return 1;
	}
	int n;
    char *line = NULL;
    cgetline(&line, 0, f);
    n = atoi(line);

	gvec_t vec = gvec_create(n, gtype_free_rbm);
	rbm_t tmp;
	int dli;
	char *word;

	while(cgetline(&line, 0, f)) {
		dli = atoi(strtok(line, " \n"));
		rbm_t tmp = rbm_create(gtype_cmp_s, gtype_free_s, NULL);
		for(int i = 0; i < dli; ++i) {
			word = strdup(strtok(NULL, " \n"));
			rbm_ires res = rbm_insert(tmp, gtype_s(word), gtype_l(1));	
	    	if (!res.inserted) {
	    		res.value->l++;
	    		free(word);
	    	}
		}
		gvec_append(vec, gtype_rbm(tmp));
    }
    free(line);

    gvec_traverse(cur, vec) {
    	tmp = cur->rbm;
    	printf("%ld - ", rbm_size(tmp));
    	rbm_traverse(key, value, tmp) {
			printf("%s:%ld ", key->s, value->l);
		}
		printf("\n");
    }

    gvec_free(vec);
    fclose(f);
	return 0;
}