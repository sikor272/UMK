#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct {
	char nazwa[100];
	int osoby;
	int procent;
} wynik_wojewodztwa;

int main(int argc, char **argv)
{
	int plik,zapis;
	char *tmp;
	char linia[16][255];
	char *text;
	wynik_wojewodztwa *dane;
	int i,j,zdawalo,zdalo,l,k;

    text = malloc(255 * sizeof(char));
    tmp = malloc(400 * sizeof(char));
	dane = malloc(16 * sizeof(wynik_wojewodztwa));
	plik = open("matury.txt", O_RDONLY);
	zapis = open("wyniki.txt", O_WRONLY);

	if(plik < 0 || zapis < 0){
		perror("Nie udalo sie otworzyc pliku");
		return -1;
	}

	zdawalo = 0;
	zdalo = 0;

	k = 0;
	l = 0;
	while(read(plik, tmp, 400) > 0){
		for(j = 0; j < strlen(tmp) && l < 16; j++){
			if(tmp[j] == '\n'){
				linia[l][k] = '\0';
				k = 0;
				l++;
			} else {
                linia[l][k] = tmp[j];
                k++;
			}
		}
	}

	for(i = 0; i < 16; i++){
		sscanf(linia[i], "%s %i %i%%", dane[i].nazwa, &dane[i].osoby, &dane[i].procent);
		zdawalo += dane[i].osoby;
		zdalo += (dane[i].osoby * dane[i].procent / 100);
	}

	sprintf(text, "W kraju zdawalo : %i osob\n", zdawalo);
    write(zapis, text, strlen(text));

    sprintf(text, "W tym zdalo : %i osob\n\n", zdalo);
    write(zapis, text, strlen(text));

    sprintf(text, "W poszczegolnych wojewodztwach zdalo:\n");
    write(zapis, text, strlen(text));

    for(j = 0; j < i; j++){
        sprintf(text, "W %s zdalo : %i osob\n", dane[j].nazwa, (dane[j].osoby * dane[j].procent / 100));
        write(zapis, text, strlen(text));
	}

	close(plik);
	close(zapis);
	return 0;
}

