#include <stdio.h>
#define SWAP(X,Y) (X = X + Y, Y = X - Y, X = X - Y)

int silnia_rek(int num){
	if(num < 2){
		return 1;
	}
		return num * silnia_rek(num - 1);
}

int silnia_iter(int num){
	int wynik = 1, i;
	for(i = 2; i <= num; i++){
		wynik *=i;
	}
	return wynik;
}

void swap_int(int *a, int *b){
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

void sortuj(int *tab, int n){
	int i,j;
	
	for(i = 0; i < n - 1; i++){
		for(j = i + 1; j > 0; j--){
			if(tab[j] < tab[j-1]){
				swap_int(&tab[j], &tab[j-1]);
			}
		}
	}
	return;
}

int main(int argc, char **argv)
{
	int i,a,b,tab[4]={4,1,6,3};
	
	a = 10;
	b = 15;
	
	printf("%d\n", silnia_rek(10));
	printf("%d\n", silnia_iter(9));
	
	printf("%d %d\n", a, b);
	swap_int(&a, &b);
	printf("%d %d\n", a, b);
	SWAP(a, b);
	printf("%d %d\n", a, b);
	
	sortuj(tab,4);
	for(i = 0; i < 4; i++){
		printf("%d ", tab[i]);
	}
	return 0;
}

