#include <iostream>
#include <cmath>
using namespace std;
/*
	Dawid Sikorski
	Zadanie 1:
		Slaby przywodca ciagu
	Zadanie 2:
		Liczenie inwersji elementow tablicy A i B
*/


/* ---- CZESC 1 ---- */ 


// Ustalamy ilosc osob do analizy
#define n 20
// Ustalamy wspolczynnik "k" dla slabego przywodcy
#define k 5
// Wprowadzamy wartosc poszczegolnej osoby do tablicy kandydatow
int kandydaci[n]={1,2,3,4,5,6,1,1,1,1,2,3,4,5,6,1,7,5,4,2};
// Tworzymy strukture do przechowywania aktualnych kandydatow
struct slaby_przywodca{
	int id;
	int ilosc;
};
int main() {
	int i,j;
	// Obliczamy wspolczynnik dla slabego przywodcy, wynik zaokraglamy w dol poniewaz szukamy wiekszej ilosci osob ( chodzi np. o przypadek 4,5 osoby ) i dodajemy jeden
	int ilosc=int(floor(n/k));
	ilosc+=1;
	// Obliczamy maksymalna ilosc slabych przywodcow, wynik zaokraglamy w dol, poniewaz liczba slabych przywodcow pomnozona przez wspolczynnik dla slabego przywodce musi byc nie wieksza niz ilosc kandydatow
	int maks=int(floor(n/ilosc));
	// Tworzymy tablice potecjalnych slabych przywodcow i zerujemy ilosc
	slaby_przywodca osoby[maks];
	for(i=0;i<maks;i++){
		osoby[i].ilosc=0;
	}
	// Rozpoczynamy szukanie potencjalnych przywodcow
	for(i=0;i<n;i++){
		// Przeszukujemy czy dana osoba nadaje sie na slabego przywodce
		for(j=0;j<maks;j++){
			// Jezeli natrafimy na pustego kandydata nadpisujemy mu identyfokator oraz zwiekszamy ilosc o jeden, oraz zatrzymujemy i przeszukujemy dalej
			if(osoby[j].ilosc==0){
				osoby[j].id=kandydaci[i];
				osoby[j].ilosc++;
				break;
			} // Jezeli natafimy na kandydata ktory juz znajdowal sie w zbiorze zwiekszamy ilosc o jeden, oraz zatrzymujemy i przeszukujemy dalej
			else
			if(osoby[j].id==kandydaci[i]){
				osoby[j].ilosc++;
				break;
			} // Jezeli podczasz sprawdzania nie natrafilismy na zadengo kandydata, wszystkim zmiejszamy ilosc oraz wspolczynnik na slabego przywodce o jeden
			else
			if(j==maks-1){
				for(j=0;j<maks;j++){
					osoby[j].ilosc--;
				}
				ilosc--;
			}
		}
	}
	cout<<"Slabi przywodcy:\n";
	// Na koniec wystarczy sprawdzic czy dany kandydat spelnia warunek wystepowania
	for(i=0;i<maks;i++){
		// Jezeli wystepowal conajmniej zadana ilosc razy dana do wspolczynnika na slabego przywodce nalezy go wypisac
		if(osoby[i].ilosc>=ilosc){
			cout<<osoby[i].id<<"\n";
		}
	}
	cout<<"\n";
	cout<<"--------------------------------";
	cout<<"\n";
	/* ---- CZESC 2 ---- */
	
	
	// Okreslamy rozmiaty tablicy A
	int p;
	p=5;
	// Okreslamy rozmiaty tablicy B
	int m;
	m=10;
	// Podajemy n posortowanych elementow tablicy A
	int A[p]={1,2,3,4,5};
	// Podajemy m posortowanych elementow tablicy B
	int B[m]={1,1,2,2,3,3,4,4,5,5};
	// Nadajemy wartosc ostatnich indeksow tablic
	i=p-1;
	j=m-1;
	// Zerujemy zmienna do liczenia wartosci inwersji
	int suma=0;
	// Sprawdzamy dwie tablice do momentu wyjscia z zakresu jednej z nich
	while(i>=0 && j>=0){
		// Je¿eli element i-ty tablicy A jest wiêkszy od elementu j-tego tablicy B
		if(A[i]>B[j]){
			// Do sumy dodajemy iloœæ pozosta³ych elementow j+1 (ze wzgledu na indeksowanie)
			suma=suma+j+1;
			// Czyli dodajemy inwersje:
			// (i,j);
			// (i,j-1);
			// (...,...);
			// (i,0);
			// Oraz zmniejszamy indeks tablicy A o jeden
			i--;
		}
		// Je¿eli element i-ty tablicy A jest mniejszy lub rowny od elementu j-tego tablicy B
		if(A[i]<=B[j]){
			// Zmiejszamy indeks tablicy B o jeden, poniwaz na mniejszych indeksach moga znajdywac sie mniejsze liczby spelniajace warunek
			j--;
		}
	}
	// Wypisujemy liczbe inwersji
	cout<<"Liczba inwersji:\n"<<suma<<"\n";
	return 0;
}
