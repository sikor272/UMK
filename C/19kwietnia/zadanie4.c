#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI acos(-1.0)
enum wybor {KONIEC, WYSOKOSC, BOK, KAT};

void menu(){
	printf("[1]. Bok * wysokosc \n");
	printf("[2]. Boki (Wzor Herona)\n");
	printf("[3]. Dwa boki oraz kat\n");
	printf("[4]. Zakoncz\n");
}
void pole(){
	double a, b;
	
	printf("Podaj dlugosc boku oraz wysokosc:\n");
	scanf("%lf", &a);
	scanf("%lf", &b);
	printf("Pole wynosi: %lf\n", (a * b) / 2.0);
}
void boki(){
	double a, b, c;
	
	printf("Podaj dlugosci bokow:\n");
	scanf("%lf", &a);
	scanf("%lf", &b);
	scanf("%lf", &c);
	printf("Pole wynosi: %lf\n", sqrt((a + b + c) * (a + b - c) * (a - b + c) * (b + c - a)) / 4.0);
	
}
void sinus(){
	double a, b, c;
	
	printf("Podaj dlugosci bokow oraz kat(w stopniach):\n");
	scanf("%lf", &a);
	scanf("%lf", &b);
	scanf("%lf", &c);
	c = c * PI / 180;
	printf("Pole wynosi: %lf\n", a * b * sin(c) / 2.0);
}

int main(int argc, char **argv)
{
	enum wybor wczytaj;
	int n;
	
	while(1){
		menu();
		scanf("%d", &n);
		system("clear");
		wczytaj = n % 4;
		switch(wczytaj){
			case KONIEC:
				exit(0);
			case WYSOKOSC:
				pole();
				break;
			case BOK:
				boki();
				break;
			case KAT:
				sinus();
				break;
			default:
				break;
		}
	}
	return 0;
}

