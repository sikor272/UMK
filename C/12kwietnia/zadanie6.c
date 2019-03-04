#include <stdio.h>
enum dokladnosc {Z, R};

int main(int argc, char **argv)
{
	int k,a,b,c;
	enum dokladnosc wynik;
	FILE *plik;
	
	plik = fopen("liczby.txt", "r");
	if(plik == NULL){
		printf("Nie udalo sie otworzyc pliku!\n");
		return -1;
	}
	
	printf("W jakim trybie chcesz pracowac?\n[1].Calkowite\n[2].Rzeczywiste\n");
	scanf("%i", &k);
	
	if(k == 1){
		wynik = Z;
	} else if(k == 2){
		wynik = R;
	} else {
		printf("Blad wybodu!\n");
		return -1;
	}
	
	while(fscanf(plik,"%i %i %i", &a, &b, &c) != EOF){
		if(wynik == Z){
			printf("%i\n", (a + b + c) / 3);
		}
		if(wynik == R){
			printf("%f\n", (a + b + c) / 3.0);
		}
	}
	
	fclose(plik);
	return 0;
}

