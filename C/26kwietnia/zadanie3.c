#include <stdio.h>
#include <stdlib.h>
int fibonacci(unsigned int szukana){
	static unsigned int *wynik;
	static unsigned int rozmiar = 0;
	static unsigned int aktualny = 0;
	
	if(rozmiar < 2){
		wynik = malloc(sizeof(unsigned int) * 2);
		wynik[0] = 0;
		wynik[1] = 1;
		rozmiar = 2;
		aktualny = 1;
	}
	while(szukana >= rozmiar){
		wynik = realloc(wynik, 100);
		rozmiar += 100;
	}
	if(szukana < aktualny){
		return wynik[szukana];
	}
	for(aktualny++; aktualny <= szukana; aktualny++){
		wynik[aktualny] = wynik[aktualny - 1] + wynik[aktualny - 2];
	}
	return wynik[szukana];
}

int main(int argc, char **argv)
{
	printf("%i", fibonacci(10));
	
	return 0;
}

