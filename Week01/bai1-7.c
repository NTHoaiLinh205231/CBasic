#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
	char a[][10]={"the", "a", "one", "some", "any"}; 
	char n[][10]={"boy", "girl", "dog", "town", "car"};
	char v[][10]={"drove", "jumped", "ran", "walked", "skipped"};
	char p[][10]={"to", "from", "over", "under", "on"};
	srand(time(NULL));
	for (int i=0; i<10; i++) {
		int j=rand()%5;
		printf("%c%s ", a[j][0]-32, a[j]+1);
		printf("%s ", n[rand()%5]);
		printf("%s ", v[rand()%5]);
		printf("%s ", p[rand()%5]);
		printf("%s ", a[rand()%5]);
		printf("%s", n[rand()%5]);
		printf(".\n");
	}
	return 0;
}