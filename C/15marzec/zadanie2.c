#include <stdio.h>
#include <ctype.h>
int main(int argc, char **argv)
{
	FILE *plik,*plik2;
	int znak, ilosc = 0, wiersz[1024], w = 0, i = 0;
	plik = fopen("dane.txt", "r");
	if (plik == NULL){
		perror("Nie moge otworzyc pliku z danymi");
		return -1;
	}
	znak = getc(plik);
	while(znak != EOF){
		printf("%c",znak);
		znak = getc(plik);
		ilosc++;
		i++;
		if((char)znak == '\n'){
			wiersz[w] = i;
			w++;
			i = 0;
		}
	}
	printf("Ilosc znakow %i\n",ilosc);
	for(i = 0; i < w; i++)
	{
		printf("Ilosc znakow w wierszu %i : %i\n", i, wiersz[i]);
	}
	fclose(plik);
	plik = fopen("dane.txt", "r");
	plik2 = fopen("wynik.txt", "w");
	znak = getc(plik);
	while(znak != EOF){
		printf("%c",toupper(znak));
		fprintf(plik2,"%c",toupper(znak));
		znak = getc(plik);
	}
	fclose(plik);
	return 0;
}

