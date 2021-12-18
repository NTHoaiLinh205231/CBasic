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

typedef struct word{
	char *w;
	int n;
} word;
#define to_word(n) (*(const word *)n)
int cmp_word(const void *a, const void *b) {
	return to_word(b).n - to_word(a).n;
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
	
	word *diffwords = malloc(l1 * sizeof(word));
	int n = 1;
	int idx2 = 0;
	diffwords[0].w = a[0];
	for (int i = 1; i < l1; i++) {
		if (!strcmp(a[i], a[i-1])) {
			//printf("%s  ==  %s\n", a[i-1], a[i]);
			n++;
			if (i == l1-1) diffwords[idx2].n = n;
		}
		else {
			//printf("%s  ><  %s\n", a[i-1], a[i]);
			diffwords[idx2].n = n;
			idx2++;
			diffwords[idx2].w = a[i];
			diffwords[idx2].n = 1;
			n = 1; 
		}
	}
	qsort(diffwords, idx2, sizeof(word), cmp_word);
  printf("So luong tu duy nhat: %d\n", idx2 + 1);
  printf("10 tu xuat hien nhieu nhat\n");
  for(int i = 0; i < 10; i++){
    printf("%-20s : %6d lan\n", diffwords[i].w, diffwords[i].n);
  }
	fclose(f);
	sll_free_list(list);
	free(a);
	free(diffwords);
	clock_t end = clock();
	double time_process = (double) (end - start) / CLOCKS_PER_SEC;
	printf("Thoi gian xu ly: %lf\n", time_process);
	return 0;
}