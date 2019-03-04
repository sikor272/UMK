#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int wiek;
    char imie[25];
    char nazwisko[25];
    float srednia;
} Osoba;

int ilosc_linii(const char *nazwa){
    int ilosc = 0;
    int c;
    FILE *plik;

    if ((plik = fopen(nazwa, "r")) == NULL){
        perror("Nie moge otworzyc pliku");
        exit(-1);
    }

    for(c = fgetc(plik); c != EOF; c = fgetc(plik)){
        ilosc += (c == '\n');
    }

    fclose(plik);
    return ilosc;
}
int compare(const void *a, const void *b){
    Osoba *c,*d;
    c = (Osoba *) a;
    d = (Osoba *) b;
    return c->srednia < d->srednia ? 1 : 0;
}
int main(int argc, char **argv)
{
	char *nazwa,*linia;
	FILE *plik,*zapis;
    Osoba *dane;
    int n,i,j;

	nazwa = malloc(sizeof(char)*10);
	linia = malloc(sizeof(char)*255);
	nazwa = "dane.txt";

	if ((plik = fopen(nazwa, "r")) == NULL || (zapis = fopen("wynik.txt", "w")) == NULL){
        perror("Nie moge otworzyc pliku");
        exit(-1);
    }
    n = ilosc_linii(nazwa);
    dane = malloc(sizeof(Osoba) * n);

    i = 0;
    while(fgets(linia, 255, plik) != NULL){
		sscanf(linia, "%s %s %u %f", dane[i].imie, dane[i].nazwisko, &dane[i].wiek, &dane[i].srednia);
		i++;
	}
	qsort(dane, n, sizeof(Osoba), compare);

	for(i = 0; i < n; i++){
        fprintf(zapis, "%s %s %u %f\n", dane[i].imie, dane[i].nazwisko, dane[i].wiek, dane[i].srednia);
	}

	fclose(plik);
	fclose(zapis);
	return 0;
}

