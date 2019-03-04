#include <stdio.h>
#include <stdlib.h>
enum wypis { NATURAL = 0, REAL = 1 }; 
int main(int argc, char **argv)
{
	FILE *plik;
	enum wypis czytaj;
	int a, b, c;
	
	plik = fopen("liczby.txt", "r");
	if(plik == NULL){
		fprintf(stderr, "Nie udalo sie otworzyc pliku!");
		exit(-1);
	}
	
	printf("Podaj dokladnosc:\n[0].INT\n[1].DOUBLE\n");
	scanf("%d", &a);
	
	if(a > 1 || a < 0){
		fprintf(stderr, "Wybrano bledny typ danych!");
		exit(-2);
	}
	czytaj = a;
	while(fscanf(plik, "%d %d %d", &a, &b, &c) == 3){
		switch(czytaj){
			case NATURAL:{
				printf("Srednia liczby %d %d %d : (int)%d\n", a, b, c, (a + b + c) / 3);
				break;
			}
			case REAL:{
				printf("Srednia liczby %d %d %d : (real)%.2f\n", a, b, c, (a + b + c) / 3.0);
				break;
			}
			default:{
				break;
			}
			
		}
	}
	fclose(plik);
	return 0;
}

