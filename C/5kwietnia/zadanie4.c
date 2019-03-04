#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
		FILE *plik;
		int rozmiar, liczba, i ,j;
		int **macierz;
		long long int suma;
	
		/* Otwieramy plik */
		plik = fopen("macierz.txt","r");
        if(plik == NULL){
        	printf("Nie udalo sie otworzyc pliku!\n");
        	return -1;
		}
		
		fscanf(plik, "%i", &rozmiar);
		
		/* Alokujemy pamiec dla 1 wymiaru */
		macierz = malloc(rozmiar * sizeof(int*));
		/* Nadajemy pamiec nowej liscie */
		for(i = 0; i < rozmiar; i++){
			macierz[i] = malloc(rozmiar * sizeof(int));
		}
        
        /* Wczytujemy dane do macierzy */
        for(i = 0; i < rozmiar; i++){
			for(j= 0; j < rozmiar; j++){
				fscanf(plik, "%i", &macierz[i][j]);
			}
		}
        
        /* Sumujemy elementy po przekatnej */
        suma = 0;
        for(i = 0; i < rozmiar; i++){
			suma += macierz[i][i];
		}
        /* Wypisujemy wynik */
        printf("Slad macierzy: %lli", suma);
        
        /* Zwalniamy pamiec */
        for(i = 0; i < rozmiar; i++){
			free(macierz[i]);
		}
		free(macierz);
        return 0;
}
