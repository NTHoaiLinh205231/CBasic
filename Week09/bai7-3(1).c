#include <stdio.h>
#include "ext/io.h"
#include "cgen.h"

typedef char* pchar;
#define to_s(p) (*(const pchar*)p)
int cmp_inc_s(const void *a, const void *b) {
	//printf("%s  %s\n", to_s(a), to_s(b));
	return strcmp(to_s(a), to_s(b));
}

typedef struct word{
	char *w;
	int n;
} word;
#define to_word(n) (*(const word *)n)
int cmp_word(const void *a, const void *b) {
	return to_word(b).n - to_word(a).n;
}

int main(int argc, char *argv[]) {
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

	word *diffwords = malloc(l1 * sizeof(word));
	int n = 0;
	int idx2 = 0;
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
	//qsort(diffwords, idx2, sizeof(word), cmp_word);
  printf("So luong tu duy nhat: %d\n", idx2);
  printf("10 tu xuat hien nhieu nhat\n");
  for(int i = 0; i < idx2; i++){
    printf("%-15s : %6d lan\n", diffwords[i].w, diffwords[i].n);
  }
	fclose(f);
	sll_free_list(list);
	free(a);
	free(diffwords);
	return 0;
}
