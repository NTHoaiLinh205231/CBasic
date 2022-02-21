#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cgen.h"
#include "ext/io.h"

char *line = NULL;
char *anh, *viet;
int choice = -1;
char *word;

int menu() {
	printf("\nMenu chuong trinh\n");
	printf("1. Nap tu dien\n");
	printf("2. Noi dung tu dien\n");
	printf("3. Them/Sua tu\n");
	printf("4. Dich cau Anh - Viet\n");
	printf("5. Thoat\n");
	printf("Ban muon thuc hien chuc nang nao? [1-5]: ");

	do {
		scanf("%d", &choice);
		if (choice >= 1 && choice <= 5) {
			break;
		} else {
			printf("Hay chon chuc nang [1-5]: ");
		}
	} while (1);
	return choice;
}

int func1(const char *fname, rbm_t tree) {
	FILE *inp = fopen(fname, "r");
	if (!inp) {
		printf("Loi mo tep %s.", fname);
		return 1;
	}

	while (cgetline(&line, 0, inp)) {
		remove_tail_lf(line);
		printf("%s\n", line);
		anh = strdup(strtok(line, " \n"));
		viet = strdup(strtok(NULL, " \n"));
		rbm_insert(tree, gtype_s(anh), gtype_s(viet));
	}
	fclose(inp);
	return 0;
}

void func2(rbm_t tree) {
	rbm_traverse(key, value, tree) {
		printf("%s %s\n", key->s, value->s);
	}
}

void func3(rbm_t tree) {
	char ch;
	printf("Hay nhap mot tu tieng anh: ");
	scanf("%s", anh);
	clear_stdin();
	gtype *v = rbm_value(tree, gtype_s(anh));
	if (v != NULL) {
		printf("Da co trong tu dien: %s - %s\n", anh, v->s);
		printf("Ban co muon nhap noi dung moi cho tu nay khong? (y/n) ");
		scanf("%c", &ch);
		clear_stdin();
		if (ch == 'y') {
			printf("Nhap noi dung thay the: ");
			scanf("%s", viet);
			free(rbm_value(tree, gtype_s(anh))->s);
			rbm_value(tree, gtype_s(anh))->s = strdup(viet);
		}
	} else {
		printf("Chua co trong tu dien.\n");
		printf("Nhap tu giai nghia: ");
		scanf("%s", viet);
		clear_stdin();
		rbm_insert(tree, gtype_s(strdup(anh)), gtype_s(strdup(viet)));
	}
}

char *strlwr(char* s){
    char* tmp = s;
    for (;*tmp;++tmp){
        *tmp = tolower((unsigned char) *tmp);
    }
    return s;
}

void func4(rbm_t tree) {
	int count = 1;
	char ch = 'y';
	printf("Hay nhap mot cau tieng anh: ");
	cgetline(&line, 0, stdin);
	remove_tail_lf(line);
	line = strlwr(line);

	char *tmp = strdup(line);
	word = strtok(tmp, " \n");
	while(word != NULL){
       	printf("%s\n", word);
       	word = strtok(NULL, " \n");
	}
	free(tmp);

	while (ch == 'y' && count != 0) {
		count = 0;
		char *tmp = strdup(line);
		word = strtok(tmp, " \n");
		while(word != NULL){
       		if (rbm_value(tree, gtype_s(word))) {
       			printf("%s ", rbm_value(tree, gtype_s(word))->s);
       		} else {
       			printf("<thieu_tu> ");
       			count++;
       		}
       		word = strtok(NULL, " \n");
		}
		printf("\n");
		if (count > 0) {
			printf("Ban co muon nhap noi dung cho tu con thieu khong? (y/n) ");
			scanf("%c", &ch);
		printf("Tu vua nhap: %c\n", ch);
			clear_stdin();
			if (ch == 'y') {
				func3(tree);
			} else {
				free(tmp);
				break;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog dict.txt\n");
		return 1;
	}

	rbm_t tree = rbm_create(gtype_cmp_s, gtype_free_s, gtype_free_s);

	do {
		menu();
		clear_stdin();
	    if (choice == 1) {
	    	func1(argv[1], tree);
	    } else if (choice == 2) {
	    	func2(tree);
	    } else if (choice == 3) {
	    	func3(tree);
	    } else if (choice == 4) {
	    	func4(tree);
	    } else {
	    	break;
	    }
	} while(1);
	free(line);
	rbm_free(tree);
	return 0;
}