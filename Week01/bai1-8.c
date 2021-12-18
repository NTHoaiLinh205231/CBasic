#include <stdio.h>

int main(int argc, char *argv[]){
    if (argc!=3) {
        printf("Usage: ./p 100 200\n");
        return 0;
    }
    double x, //argv[1]
           y; //argv[2]
    sscanf(argv[1], "%lf", &x);
    sscanf(argv[2], "%lf", &y);
    printf("Dien tich HCN la %g\nChu vi HCN la %g\n", x*y, (x+y)*2);
    return 0;
}
