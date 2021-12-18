#include<stdio.h>

int menu1() {
	int ch;
	do {
		printf("1. Xem danh sach bai hat\n");
		printf("2. Loc danh sach bai hat\n");
		printf("3. Them bai hat\n");
		printf("4. Xoa bai hat\n");
		printf("5. Thoat\n");
		printf("Lua chon cua ban la [1, 2, 3, 4, 5]?  ");
		scanf("%d", &ch);
    } while(ch < 1 || ch > 5);
	return ch;
}

int menu2() {
	int ch;
	do {
		printf("Loc danh sach bai hat theo:\n");
		printf("1. Ten bai hat\n");
		printf("2. Ca si\n");
		printf("3. Nhac si\n");
		printf("4. Nam sang tac\n");
		printf("Lua chon cua ban la [1, 2, 3, 4]?  ");
		scanf("%d", &ch);
    } while(ch < 1 || ch > 4);
	return ch;
}