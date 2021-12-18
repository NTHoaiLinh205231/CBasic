#include <stdio.h>

void split(double x, int *a, double *b) {
    *a=(int) x;
    *b=x-*a;
}

int main() {
    double x;
    int a;
    double b;
    printf("Nhap mot so thuc: ");
    scanf("%lf", &x);
    split(x, &a, &b);
    printf("Phan nguyen la: %d\nPhan thap phan la: %g\n", a, b);
    return 0;
}
