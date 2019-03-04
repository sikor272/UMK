#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char nazwa[100];
	int osoby;
	int procent;
	int zdalo;
} wynik_wojewodztwa;

int alfabet(const void *a, const void *b){
	wynik_wojewodztwa *i,*j;
	
	i = (wynik_wojewodztwa *) a;
	j = (wynik_wojewodztwa *) b;
	return strcmp(i->nazwa, j->nazwa);
}

int zdajacy(const void *a, const void *b){
	wynik_wojewodztwa *i,*j;
	
	i = (wynik_wojewodztwa *) a;
	j = (wynik_wojewodztwa *) b;
	return i->osoby - j->osoby;
}

int odsetek(const void *a, const void *b){
	wynik_wojewodztwa *i,*j;
	
	i = (wynik_wojewodztwa *) a;
	j = (wynik_wojewodztwa *) b;
	return i->osoby - j->osoby;
}

int main(int argc, char **argv)
{
	FILE *plik;
	char buffor[255];
	wynik_wojewodztwa *dane;
	int i,j;
	
	dane = malloc(16 * sizeof(wynik_wojewodztwa));
	plik = fopen("matury.txt", "r");
	
	if(plik == NULL){
		perror("Nie udalo sie otworzyc pliku");
		return -1;
	}
	
	i = 0;
	while(fgets(buffor, 255, plik) != NULL){
		sscanf(buffor, "%s %i %i%%", dane[i].nazwa, &dane[i].osoby, &dane[i].procent);
		dane[i].zdalo = (dane[i].osoby * dane[i].procent / 100);
		i++;
	}
	
	printf("Posortowane alfabetycznie:\n");
	qsort(dane, i, sizeof(wynik_wojewodztwa), alfabet);
	for(j = 0; j < i; j++){
		printf("%s %i %i%% %i\n", dane[j].nazwa, dane[j].osoby, dane[j].procent, dane[j].zdalo);
	}
	
	printf("\nPosortowane rosnaco po ilosci osob ktore zdawaly:\n");
	qsort(dane, i, sizeof(wynik_wojewodztwa), zdajacy);
	for(j = 0; j < i; j++){
		printf("%s %i %i%% %i\n", dane[j].nazwa, dane[j].osoby, dane[j].procent, dane[j].zdalo);
	}
	
	printf("\nPosortowane rosnaco po ilosci osob ktore zdaly:\n");
	qsort(dane, i, sizeof(wynik_wojewodztwa), odsetek);
	for(j = 0; j < i; j++){
		printf("%s %i %i%% %i\n", dane[j].nazwa, dane[j].osoby, dane[j].procent, dane[j].zdalo);
	}
	
	fclose(plik);
	return 0;
}

