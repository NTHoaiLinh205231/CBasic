#include <stdio.h>
#include "ext/io.h"
#include "cgen.h"
#include <time.h>

typedef char* pchar;
#define to_s(p) (*(const pchar*)p)
int cmp_inc_s(const void *a, const void *b) { 
	//printf("%s  %s\n", to_s(a), to_s(b));
	return strcmp(to_s(a), to_s(b));
}

typedef struct words_s{
	struct sll_node_s base;
	char *w;
	int n;
} *words;

#define to_words(n) ((words)n)

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

int main(int argc, char *argv[]) {
	clock_t start = clock();
	if ((argc != 2)) {
		printf("Usage: ./prog text.txt\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Loi mo tep %s\n", argv[1]);
		return 1;
	}
	int i = 0;
	char buff[1024];
	sll_t list = sll_create_list();
	while (!feof(f)) {
		fscanf(f, "%s", buff);
		//printf("%s\n", buff);
		sll_push_back_g(list, (gtype){.s = strdup(buff)});
		i++;
	}
	/*printf("%d\n", i);
	sll_traverse(cur, list) {
		printf("%s  ", sll_node_g_value(cur).s);
	}*/
	long l1 = sll_length(list);
	printf("Tong so tu trong file: %ld\n", l1);
	pchar *a = malloc(l1 * sizeof(pchar));
	int idx1 = 0;
	sll_traverse(cur, list) {
		a[idx1++] = sll_node_g_value(cur).s;
	}
	qsort(a, l1, sizeof(a[0]), cmp_inc_s);
	sll_t diffwords = sll_create_list();
	int n = 0;
	/*sll_push_back_word(diffwords, "Linh", n);
	sll_traverse(cur, diffwords) {
  	words node = to_words(cur);
		printf("word: %s and number: %d\n", node->w, node->n);
	}*/
	for (int i = 0; i < l1; i++) {
		if (i < l1-1) {
			if (strcmp(a[i], a[i+1])) {
				//printf("%s  ><  %s\n", a[i], a[i+1]);
				n++;
				sll_push_back_word(diffwords, a[i], n);
				if (i < l1-1) n = 0; else n = 1;
			}
			else {
				//printf("%s  ==  %s\n", a[i], a[i+1]);
				n++;
			}
		} else {
			if (strcmp(a[i-1], a[i])) {
				//printf("%s  ><  %s\n", a[i-1], a[i]);
				n++;
				sll_push_back_word(diffwords, a[i], n);
			}
			else {
				//printf("%s  ==  %s\n", a[i-1], a[i]);
				n++;
				sll_push_back_word(diffwords, a[i], n);
			}
		}
	}
	long l2 = sll_length(diffwords);	
	printf("So tu duy nhat: %ld\n", l2);
	int *b = malloc(l2 * sizeof(int));
	int idx2 = 0;
	sll_traverse(cur, diffwords) {
  	words node1 = to_words(cur);
		//printf("word: %s and number: %d\n", node1->w, node1->n);
		b[idx2++] = node1->n;
	}
	for (int i = 0; i < l2; i++) {
		for (int j = i + 1; j < l2; j++) {
			if (b[i] < b[j]) {
				int tmp = b[i];
				b[i] = b[j];
				b[j] = tmp;
			}
		}
	}
	printf("10 tu xuat hien nhieu nhat:\n");
	sll_traverse(cur, diffwords) {
  	words node2 = to_words(cur);
		if (node2->n > b[10]) printf("%s - %d\n", node2->w, node2->n);
	}
	fclose(f);
	sll_free_list(list);
	sll_free_list(diffwords);
	free(a);
	free(b);
	clock_t end = clock();
	double time_process = (double) (end - start) / CLOCKS_PER_SEC;
	printf("Thoi gian xu ly: %lf\n", time_process);
	return 0;
}



/*
	for (int i = 0; i < l1; i++) {
		if (i < l1-1) {
				if (strcmp(a[i], a[i+1])) {
					//printf("%s  ><  %s\n", a[i], a[i+1]);
					n++;
					diffwords[idx2].w = a[i];
					diffwords[idx2].n = n;
					idx2++;
					if (i < l1-1) n = 0; else n = 1;
				}
				else {
					//printf("%s  ==  %s\n", a[i], a[i+1]);
					n++;
				}
		} else {
				if (strcmp(a[i-1], a[i])) {
					//printf("%s  ><  %s\n", a[i-1], a[i]);
					n++;
					diffwords[idx2].w = a[i];
					diffwords[idx2].n = n;
					idx2++;
				}
				else {
					//printf("%s  ==  %s\n", a[i-1], a[i]);
					n++;
					diffwords[idx2].w = a[i];
					diffwords[idx2].n = n;
					idx2++;
				}
		}
	}*/