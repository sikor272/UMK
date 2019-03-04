#include <stdio.h>

typedef union {
    int calkowita;
    double rzeczywista;
} Liczba;

int main(int argc, char **argv)
{
	int k;
	Liczba wczytaj;
	
	printf("W jakim trybie chcesz pracowac?\n[1].Calkowite\n[2].Rzeczywiste\n");
	scanf("%i", &k);
	
	if(k == 1){
		printf("Podaj liczbe calkowita:\n");
		scanf("%i", &wczytaj.calkowita);
		printf("%i\n", wczytaj.calkowita*wczytaj.calkowita);
	} else if(k == 2){
		printf("Podaj liczbe rzeczywista:\n");
		scanf("%lf", &wczytaj.rzeczywista);
		printf("%lf\n", wczytaj.rzeczywista*wczytaj.rzeczywista);
	}
	
	return 0;
}

