#include <stdio.h>

int sosanh(int a[], int b[], int n)
{
    for (int i=0; i<n; i++) {
        if (a[i]!=b[i]) return 0;
    }
    return 1;
}

int main()
{
    int a[100], b[100], n;
    printf("Nhap so phan tu cua mang: ");
    scanf("%d", &n);
    printf("Nhap mang thu nhat: \n");
    for (int i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    printf("Nhap mang thu nhat: \n");
    for (int i=0; i<n; i++) {
        scanf("%d", &b[i]);
    }
    printf("Ket qua: %d", sosanh(a,b,n));
    return 0;
}
