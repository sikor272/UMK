#include <iostream>
using namespace std;
/*
	Dawid Sikorski
	Sortowanie przez wstawianie
*/


void InsertSort(int dane[],int start,int koniec){
	// Zmienne pomocnicze
	int pomocnicza,i,j;
	for (i = 1; i < koniec; i++){
		// Zapamietujemy aktualny element do zmiennej pomocniczej
		pomocnicza = dane[i];
		// Sprawdzamy poprzednie elementy
		for (j = i-1; j >= 0; j--){
			// Jezeli poprzedni element jest mniejszy przenosimy go o jeden w prawo
			if (pomocnicza < dane[j])
				dane[j+1] = dane[j];
			else // W przeciwnym wypadku mamy juz posortowane dane do aktualnego miejsca
				break;
		}
		// W aktualnie puste miejsce wstawiamy zapamietany element z ktorym porownywalismy wczesniejsze
		dane[j+1] = pomocnicza;
	}
}
int main() {
	// Wprowadzamy dane do posortowania
	int dane[4]={7,1,0,9};
	// Wypisujemy dane przed posortowaniem
	for(int i=0;i<4;i++){
		cout.width(2);cout<<dane[i];
	}
	cout<<"\n";
	// Sortujemy dane
	InsertSort(dane,0,4);
	// Wypisujemy dane posortowane niemalejaco
	for(int i=0;i<4;i++){
		cout.width(2);cout<<dane[i];
	}
	return 0;
}
