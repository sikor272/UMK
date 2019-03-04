#include <iostream>
using namespace std;
/*
	Dawid Sikorski
	Sortowanie szybkie
*/



void MergeSort(int dane[],int poczatek, int koniec)
{
	// Jezeli jestesmy w zbiorze 1 elementowym nie mamy co sortowac
	if(poczatek==koniec)
		return;
	// Deklarujemy element srodkowy zbioru
	int srodek;
	srodek=(poczatek+koniec)/2;
	// Sortujemy lewa czesc tablicy
	MergeSort(dane,poczatek,srodek);
	// Sortujemt prawa czesc tablicy
	MergeSort(dane,srodek+1,koniec);
	
	// A nastepnie bedziemy laczyc dwie czesci
	// Deklarujemy tablice pomocnicza i przepisujemy do niej wartosci tablicy glownej
	int pomocnicza[koniec+1];
	for(int i=poczatek;i<=koniec;i++)
		pomocnicza[i]=dane[i];
	// Deklarujemy zmienne pomocnicze
	int i,j,r;
	// Nadajemy wartosc poczatka dla "i" i "r"
	i=poczatek;
	r=poczatek;
	// Nadajemy wartosc nastepna po elemencie srodkowym dla "j" poniewaz bedziemy laczyc dwie polowki
	j=srodek+1;
	// Rozpoczynamy scalanie dwoch posortowanych polowek:
	// Lewej od poczatku do srodka oraz prawej od nastepnika srodka do konca
	while(i<=srodek && j<=koniec){
		// Jezeli element i-ty w lewej polowce jest mniejszy od elementu j-tego w prawej polowce (za pomoca tablicy pomocniczej)
		 if(pomocnicza[i]<pomocnicza[j]){
		 	// To na r'tej pozycji w glownej tablicy nalezy nadpisac element i-ty
		 	dane[r]=pomocnicza[i];
		 	// Przesuwamy sie o jeden element dalej w lewej polowce
		 	i++;
		 }// w przeciwnym razie i-ty w lewej polowce jest wiekszy lub rowny od elementu j-tego w prawej polowce (za pomoca tablicy pomocniczej)
		 else{
		 	// To na r'tej pozycji w glownej tablicy nalezy nadpisac element j-ty
		 	dane[r]=pomocnicza[j];
		 	// Przesuwamy sie o jeden element dalej w prawej polowce
		 	j++;
		 }
		 // Przesuwamy sie o jeden element w glownej tablicy
		 r++;
	}
	// Jezeli prawa czesc zostala wyczerpana a lewa nie
	// trzeba przepisac reszte elementow lewej polowki
	while(i<=srodek){
		// Na r'tej pozycji w glownej tablicy nalezy nadpisac element i-ty
		dane[r]=pomocnicza[i];
		// Przesuwamy sie o jeden element dalej w lewej polowce
		i++;
		// Przesuwamy sie o jeden element w glownej tablicy
		r++;
	}
}


int main() {
	// Wprowadzamy dane do posortowania
	int dane[4]={6,1,4,1};
	// Wypisujemy dane przed posortowaniem
	for(int i=0;i<4;i++){
		cout.width(2);cout<<dane[i];
	}
	cout<<"\n";
	// Sortujemy dane od indeksu pierwszego ( 0 ) do ostatniego ( ilosc - 1 )
	MergeSort(dane,0,3);
	// Wypisujemy dane posortowane niemalejaco
	for(int i=0;i<4;i++){
		cout.width(2);cout<<dane[i];
	}
	return 0;
}
