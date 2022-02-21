#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hang_s {
	char *id;
	char *name;
	double price;
	int quantity;
} *hang_t;

typedef struct bill_s {
	char *name;
	double price;
	int quantity;
	double total;
} *bill_t;

int choice = -1;

void gtype_free_product(gtype v) {
  hang_t ptr = v.v;
  free(ptr->id);
  free(ptr->name);
  free(ptr);
}

void gsl_free_bill(gtype v) {
	bill_t b = v.v;
	free(b->name);
	free(b);
}

int menu() {
	printf("\nMenu chuong trinh\n");
	printf("1. Xem thong tin mat hang\n");
	printf("2. Tao don hang\n");
	printf("3. Thoat\n");
	do {
		printf("Ban muon thuc hien chuc nang nao? [1-3]: ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 3);
	return choice;
}

hang_t parse_product(char *s) {
  	hang_t ptr = malloc(sizeof(struct hang_s));
  	ptr->id = strdup(strtok(s, " \n"));
  	ptr->name = strdup(strtok(NULL, " \n"));
  	sscanf(strtok(NULL, " \n"), "%lf", &ptr->price);
  	sscanf(strtok(NULL, " \n"), "%d", &ptr->quantity);
  	return ptr;
}

int parse_input(const char *inp_name, hmap_t out) {
 	FILE *inp = fopen(inp_name, "r");
  	if (!inp) {
		printf("Loi mo tep %s.\n", inp_name);
		return 1;
	}
	char *line = NULL;
	cgetline(&line, 0, inp);
	int n = 0;
	sscanf(line, "%d", &n);
	for (int i = 0; i < n; ++i) {
	    hang_t tmp = parse_product(cgetline(&line, 0, inp));
	    hmap_insert(out, gtype_s(tmp->id), gtype_v(tmp));
	}
	fclose(inp);
	free(line);
	return 0;
}

void find_product(hmap_t products) {
  	char *id = NULL;
  	printf("Nhap ID: ");
	remove_tail_lf(cgetline(&id, 0, stdin));
	gtype *value = hmap_value(products, gtype_s(id));
	if (value) {
		hang_t tmp = value->v;
		printf("%s %s %g %d\n", tmp->id, tmp->name, tmp->price, tmp->quantity);
	} else {
		printf("Khong tim thay!\n");
	}
	free(id);
}

bill_t create_item(const char *name, double price, int quantity) {
  	bill_t b = malloc(sizeof(struct bill_s));
	b->name = strdup(name);
	b->price = price;
	b->quantity = quantity;
	b->total = quantity * price;
	return b;
}

void create_bill(hmap_t products) {
  	char *id = NULL;
  	int quantity;
  	gsl_t bill = gsl_create(gsl_free_bill);
  	for (;;) {
  		printf("Nhap ID: ");
		remove_tail_lf(cgetline(&id, 0, stdin));
		if (strcmp(id, "STOP") == 0) {
			break;
		}
		gtype *value = hmap_value(products, gtype_s(id));
		if (!value) {
			printf("Khong tim thay!\n");
			continue;
		}
		hang_t item = value->v;
		printf("Nhap so luong: ");
		scanf("%d", &quantity);
		clear_stdin();
		if (quantity <= 0 || quantity > item->quantity) {
			printf("So luong khong hop le.\n");
			continue;
		} 
		bill_t b = create_item(item->name, item->price, item->quantity);
		gsl_push_back(bill, gtype_v(b));
	}
	int idx = 1;
	double tong = 0;
	printf("Cong ty ABC\nDon hang ban le\n");
	printf("%5s %18s %15s %20s %20s\n", "STT", "Mat hang", "Don gia", "So luong", "Thanh tien");
	gsl_traverse(cur, bill) {
		bill_t tmp = cur->v;
		printf("%d %20s %20.3f %15d %20.3f\n", idx, tmp->name, tmp->price, tmp->quantity, tmp->total);
		tong += tmp->total;
		idx++; 
	}
	printf("Tong tien: %3.f\n", tong);
	gsl_free(bill);
	free(id);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./prog inp.txt\n");
		return 1;
	}

	hmap_t products = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, gtype_free_product);
	parse_input(argv[1], products);

	do {
		choice = menu();
		clear_stdin();
		if (choice == 1) {
			find_product(products);
		} else if (choice == 2) {
			create_bill(products);
		} else {
			break;
		}
	} while (1);
	hmap_free(products);
	return 0;
}