#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char name[30];
    char number[20];
    char address[100];
} directory;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./prog phone1.dat phone2.dat phone.dat\n");
        return 1;
    }
    FILE *f1 = fopen(argv[1], "rb");
    if (f1 == NULL) {
        printf("Input file not found!\n");
        return 2;
    }
    FILE *f2 = fopen(argv[2], "rb");
    if (f2 == NULL) {
        printf("Input file not found!\n");
        return 2;
    }
    FILE *fo = fopen(argv[3], "wb+");
    char buff[150];
    while(fread(buff, 150, 1, f1) != 0) {
        fwrite(buff, 150, 1, fo);
    }
    while(fread(buff, 150, 1, f2) != 0) {
        fwrite(buff, 150, 1, fo);
    }
    fseek(fo, 0, SEEK_SET);
    directory check[101];
    for (int i = 0; i < 20; i++) {
        fread(&check[i], sizeof(directory), 1, fo);
        printf("%-20s %-20s %-20s\n", check[i].name, check[i].number, check[i].address);
    }
    fclose(fo);
    fclose(f1);
    fclose(f2);
    return 0;
}