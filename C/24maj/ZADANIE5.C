#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
		char nazwa_wojewodztwa[255];
		int ile_zdawalo;
		int ile_zdalo;
} wynik_wojewodztwa;

int line_of_file(const char *napis){
	int n,i;
	FILE *plik;
	char linia[255];

	plik = fopen(napis, "r");

	if(plik == NULL){
		fprintf(stderr, "Nie udalo sie otworzyc pliku!");
		exit(-1);
	}
	n = 0;
	while(fgets(linia, 255, plik) > 0){
		for(i = 0; i < strlen(linia); i++){
            n += (linia[i] == '\n');
		}
	}
	fclose(plik);
	return n;
}

int main(int argc, char **argv)
{
	wynik_wojewodztwa *dane;
	int linie,procent,i,suma_zdalo,suma_zdawalo;
	FILE *plik,*zapis;
	char linia[255];

	plik = fopen("matury.txt", "r");
	zapis = fopen("wynik.txt", "w");
	if(plik == NULL || zapis == NULL){
		perror("Nie udalo sie otworzyc pliku");
		exit(-1);
	}

	linie = line_of_file("matury.txt");
	dane = malloc(linie * sizeof(wynik_wojewodztwa));
	for(i = 0; i < linie; i++){
		fgets(linia, 255, plik);
		sscanf(linia, "%s %i %i%%", dane[i].nazwa_wojewodztwa, &dane[i].ile_zdawalo, &procent);
		dane[i].ile_zdalo = dane[i].ile_zdawalo * procent / 100;
	}

	suma_zdalo = 0;
	suma_zdawalo = 0;
	for(i = 0; i < linie; i++){
		suma_zdalo += dane[i].ile_zdalo;
		suma_zdawalo += dane[i].ile_zdawalo;
	}

	fprintf(zapis, "W kraju zdawalo %d osob,\n", suma_zdawalo);
	fprintf(zapis, "W tym zdalo %d osob.\n", suma_zdalo);
	fprintf(zapis, "W poszczegolnych wojewodztwach:\n");
	for(i = 0; i < linie; i++){
		fprintf(zapis, "%d.%s zdalo %d osob.\n", i + 1, dane[i].nazwa_wojewodztwa, dane[i].ile_zdalo);
	}

	free(dane);
	fclose(zapis);
	fclose(plik);
	return 0;
}

