#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    if (argc!=4) {
        printf("Usage: ./p a b c\n");
        return 0;
    }
    double a, b, c;
    sscanf(argv[1], "%lf", &a);
    sscanf(argv[2], "%lf", &b);
    sscanf(argv[3], "%lf", &c);
    if (a==0) {
        if (b==0) {
            printf("Phuong trinh vo nghiem\n");
        } else {
            printf("Phuong trinh co mot nghiem: x=%g\n", (-c/b));
        }
        return 0;
    }
    double delta=b*b-4*a*c;
    double x1, x2;
    if (delta>0) {
        x1=((-b+sqrt(delta))/(2*a));
        x2=((-b-sqrt(delta))/(2*a));
        printf("Phuong trinh co 2 nghiem la: x1=%g va x2=%g\n", x1, x2);
    } else if (delta==0) {
        x1=(-b/(2*a));
        printf("Phuong trinh co nghiem kep: x1=x2=%g\n", x1);
    } else {
        printf("Phuong trinh vo nghiem\n");
    }
    return 0;
}
