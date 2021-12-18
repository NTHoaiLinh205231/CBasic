#include <stdio.h>
#include <math.h>
#define N 10

int main(void) {
    double a[N];
    printf("Moi nhap %d so: \n", N);
    for (int i=0; i<N; i++) {
        scanf("%lf", &a[i]);
    }
    printf("Cac so theo thu tu nguoc lai: \n");
    for (int i=N-1; i>=0; --i) {
        printf("%g\n", a[i]);
    }
    double avg=0, min;
    for (int i=0; i<N; i++) {
        avg+=a[i];
    }
    avg=avg/N;
    min=fabs(a[0]-avg);
    printf("Cac phan tu co gia tri gan nhat voi gia tri trung binh cua mang:\n");
    for (int i=0; i<N; i++) {
        if (min>fabs(a[i]-avg)) min=fabs(a[i]-avg);
    }
    for (int i=0; i<N; i++) {
        if (min == fabs(a[i]-avg)) printf("a[%d]=%g\n", i, a[i]);
    }
    return 0;
}