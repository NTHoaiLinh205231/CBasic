#include<stdio.h>

typedef struct {
    char name[30];
    char number[20];
    char address[100];
} directory;

int main() {
    FILE *f = fopen("phonebook.dat", "rb+");
    int n;
    printf("Record number: ");
    scanf("%d", &n);
    directory dir[101];
    fseek(f, (n - 1) * sizeof(directory), SEEK_SET);
    fread(&dir[n - 1], sizeof(directory), 1, f);
    for (int i = 0; i < sizeof(dir[n - 1].address); i++) {
        dir[n - 1].address[i] = '\0';
    }
    printf("New email: ");
    scanf(" %s", dir[n - 1].address);
    fseek(f, (n - 1) * sizeof(directory), SEEK_SET);
    fwrite(&dir[n - 1], sizeof(directory), 1, f);
    fseek(f, 0, SEEK_SET);
    directory check[101];
    for (int i = 0; i < 20; i++) {
        fread(&check[i], sizeof(directory), 1, f);
        printf("%-20s %-20s %-20s\n", check[i].name, check[i].number, check[i].address);
    }
    fclose(f);
    return 0;
}