#include <stdio.h>
struct ulamek{
	int licznik;
	int mianownik;
};
int nwd(int a, int b){
	if(b == 0)
		return a;
	return nwd(b,a%b);
}
int main(int argc, char **argv)
{
	struct ulamek tab[9];
	struct ulamek wynik;
	int i,j;
	
	j = 1;
	for(i = 0; i < 9; i++){
		tab[i].licznik = j;
		j++;
		tab[i].mianownik = j;
	
	}
	wynik.licznik = tab[0].licznik;
	wynik.mianownik = tab[0].mianownik;
	
	for(i = 1 ;i < 9; i++){
		j = nwd(wynik.mianownik,tab[i].mianownik);
		wynik.licznik = (wynik.licznik * tab[i].mianownik / j) + (tab[i].licznik * wynik.mianownik / j);
		wynik.mianownik = wynik.mianownik * tab[i].mianownik / j;
		
		j = nwd(wynik.licznik,wynik.mianownik);
		wynik.licznik /= j;
		wynik.mianownik /= j;
	}
	
	printf("Wartosc 1/2 + 2/3 + 3/4 + 4/5 + 5/6 + 6/7 + 7/8 + 8/9 + 9/10 = %i/%i",wynik.licznik,wynik.mianownik);
	return 0;
}

