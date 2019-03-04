#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char nazwa[100];
	int osoby;
	int procent;
} wynik_wojewodztwa;

int main(int argc, char **argv)
{
	FILE *plik,*zapis;
	char buffor[255];
	wynik_wojewodztwa *dane;
	int i,j,zdawalo,zdalo;
	
	dane = malloc(16 * sizeof(wynik_wojewodztwa));
	plik = fopen("matury.txt", "r");
	zapis = fopen("wyniki.txt", "w");
	
	if(plik == NULL || zapis == NULL){
		perror("Nie udalo sie otworzyc pliku");
		return -1;
	}
	
	i = 0;
	zdawalo = 0;
	zdalo = 0;
	while(fgets(buffor, 255, plik) != NULL){
		sscanf(buffor, "%s %i %i%%", dane[i].nazwa, &dane[i].osoby, &dane[i].procent);
		zdawalo += dane[i].osoby;
		zdalo += (dane[i].osoby * dane[i].procent / 100);
		i++;
	}
	
	fprintf(zapis, "W kraju zdawalo : %i osob\n", zdawalo);
	fprintf(zapis, "W tym zdalo : %i osob\n\n", zdalo);
	fprintf(zapis, "W poszczegolnych wojewodztwach zdalo:\n");
	for(j = 0; j < i; j++){
		fprintf(zapis, "W %s zdalo : %i osob\n", dane[j].nazwa, (dane[j].osoby * dane[j].procent / 100));
	}

	fclose(plik);
	fclose(zapis);
	return 0;
}

