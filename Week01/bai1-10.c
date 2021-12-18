#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double Run(double x) {
	double sum = 1;
	double i = 1;
	double temp = x;
	while (temp > 1e-11) {
		sum += temp;
		i++;
		temp = temp * (x / i);
	}
	return sum;
}

int main(int argc, char *argv[]) {
	double x;
	int y;
    switch(argc) {
    	case 1: 
    		printf("Nhap x: ");
    		scanf("%lf", &x);
    		printf("e^%g = %lf\n", x, Run(x));
    		break;
    	case 2: 
    	   	sscanf(argv[1], "%lf", &x); 
    		printf("e^%g = %lf\n", x, Run(x));
    		break;
    	case 3:
    		sscanf(argv[1], "%lf", &x); 
    		sscanf(argv[2], "%d", &y);
    		printf("e^%g = %.*lf\n", x, y, Run(x));
    		break;
    	default: 
    		printf("Nhap sai cau truc\n");
    }
	return 0;
}