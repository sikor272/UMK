#include <iostream>
using namespace std;
/*
	Dawid Sikorski
	Sortowanie szybkie
*/

void quick(int dane[], int start, int koniec) {
    int wskaznik, aktualna,ostatnia;
    if(start<koniec) {
    	// Zapamietujemy pozycje poczatkowe do wskaznika oraz ostaniej zamienionej wartosci
        wskaznik = start;
        ostatnia = start;
        // Zapamietujemy pierwszy element z ktorym bedziemy porownywac dane
        aktualna = dane[wskaznik];
        for(int i=start+1; i<koniec; i++) {
        	// Jezeli dany element jest mniejszy:
            if(dane[i]<aktualna) {
            	// Zamienieniamy go z elementem wskazywanym przez wskaznik
                swap(dane[wskaznik], dane[i]);
                // Przesuwamy sie o jeden element w prawo
                wskaznik++;
                // Zapamietujemy ostatni element ktory zostal zamieniony
                ostatnia=i;
            }
        }
        // Po zakonczeniu zamieniamy ostatni zapamietany zamieniony element, z wskazywanym przez wskaznik
        // Ze wzgledu na zamienianie element na miejscu ostatnim jest wiekszy od wskazywanego przez wskaznik
        swap(dane[wskaznik], dane[ostatnia]);
        // Nastepnie wywolujemy sortowanie
		// 1. od poczatku do miejsca podzialu
        quick(dane, start, wskaznik);
        // 2. od nastepnego elementu miejsca podzialu do konca
        quick(dane, wskaznik+1, koniec);
    }
}

int main() {
    int n=4;
    // Wprowadzamy elementy do posortowania
    int dane[n]={3,1,4,2};
    // Sortujemy
    quick(dane, 0, n);
    // Wypisujemy posortowane elementy
    for(int i = 0; i < n; ++i){
            cout << dane[i] << " ";
    }
    return 0;
}
