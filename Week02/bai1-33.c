#include<stdio.h>

typedef struct {
    char name[30];
    char number[20];
    char address[100];
} directory;

int main() {
    directory dir[101];
    printf("Nhap danh ba:\n");
    printf("%-20s %-20s %-20s\n", "Name", "Number", "Address");
    for (int i = 0; i < 20; i++) {
        scanf("%s %s %s", dir[i].name, dir[i].number, dir[i].address);
    }
    FILE *f = fopen("phonebook.dat", "w+b");
    for (int i = 0; i < 20; i++) {
        fwrite(&dir[i], sizeof(directory), 1, f);
    }
    fseek(f, 0, SEEK_SET);
    directory check[101];
    for (int i = 0; i < 20; i++) {
        fread(&check[i], sizeof(directory), 1, f);
        printf("%-20s %-20s %-20s\n", check[i].name, check[i].number, check[i].address);
    }
    fclose(f);
    return 0;
}