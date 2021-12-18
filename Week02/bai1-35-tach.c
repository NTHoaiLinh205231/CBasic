#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: ./prog phone.dat N phone1.dat phone2.dat\n");
        return 1;
    }
    FILE *fi = fopen(argv[1], "rb");
    if (fi == NULL) {
        printf("Input file not found!\n");
        return 2;
    }
    FILE *f1 = fopen(argv[3], "wb");
    FILE *f2 = fopen(argv[4], "wb");
    char buff[150];
    for (int i = 0; i < atoi(argv[2]); i++) {
        fread(buff, 150, 1, fi);
        fwrite(buff, 150, 1, f1);
    }
    while(fread(buff, 150, 1, fi) != 0) {
        fwrite(buff, 150, 1, f2);
    }
    fclose(fi);
    fclose(f1);
    fclose(f2);
    return 0;
}