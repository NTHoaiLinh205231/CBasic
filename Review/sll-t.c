#include <stdio.h>
#include "ext/io.h"
#include "base/sll.h"

typedef struct words_s{
	struct sll_s base;
	char *w;
	int n;
} *words;

#define to_words(n) ((words)n)

sln_t sll_create_node_word(char *word, int number){
  sln_t tmp = sln_create();
  words nn = realloc(tmp, sizeof(struct words_s));
  nn->w = strdup(word);
  nn->n = number;
  return (sln_t) nn;
}

void printList(sll_t list){
	printf("\nTong so tu trong file: %ld\n", sll_length(list));
	sll_traverse(cur, list) {
		words cur1 = to_words(cur);
		printf("%s  ", cur1->w);
	}
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
	char *s;
	sll_t list = sll_create();
	while (!feof(f)) {
		fscanf(f, "%s", s);
		//printf("%s\n", s);
		sln_t new = sll_create_node_word(s, i+1);
		sll_push_back(list, new);
		i++;
	}
		
	if (sll_is_empty(list)) {
		printf("sll is empty\n");
		return 0;
	} else {
		printf("sll is not empty\n");
		printList(list);
	}
	
	strcpy(buff, "start");
	s = strdup(buff);
	sln_t start = sll_create_node_word(s, 0);
	sll_push_front(list, start);
	printf("\nstart->next: %s\n", to_words(start->next)->w);
	printList(list);
	free(s);

	printf("Delete all.");
	do {
		sll_pop_front(list);
	} while(!sll_is_empty(list));
	if (sll_is_empty(list)) {
		printf("\nsll is empty\n");
	} else {
		printf("\nsll is not empty\n");
	}
	fclose(f);
	sll_free(list);
	
	return 0;
}