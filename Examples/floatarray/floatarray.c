#include <stdio.h>


int main() {
	
	int i;
	int n;
	
	scanf("%d",&n);
	float niz[n];
	for(i = 0;i<n;i++)
		scanf("%f",&niz[i]);
	float suma = 0.0;
	for(i = 0;i<n;i++)
		suma += niz[i];
	printf("Suma elemenata niza je: %f\n",suma);
	
	return 0;
	
}
