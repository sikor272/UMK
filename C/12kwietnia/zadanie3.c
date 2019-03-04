#include <stdio.h>
#include <stdlib.h>

typedef struct{
	double real;
	double imagine;
} LiczbaZespolona;

LiczbaZespolona Dodawanie(LiczbaZespolona Pierwsza, LiczbaZespolona Druga){
	LiczbaZespolona result;
	
	result.real = Pierwsza.real + Druga.real;
	result.imagine = Pierwsza.imagine + Druga.imagine;
	return result;
}

LiczbaZespolona *DodawanieWskaznik(LiczbaZespolona *Pierwsza, LiczbaZespolona *Druga){
	LiczbaZespolona *result = malloc(sizeof(LiczbaZespolona));
	if(result == NULL){
		printf("Blad zaalokowania pamieci!\n");
		return Pierwsza;
	}
	result->real = Pierwsza->real + Druga->real;
	result->imagine = Pierwsza->imagine + Druga->imagine;
	return result;
}

int main(int argc, char **argv)
{
	LiczbaZespolona a, b, c, *d;
	
	a.real = 15;
	a.imagine = 3;
	
	b.real = 4.5;
	b.imagine = 4.8;
	
	c = Dodawanie(a, b);
	printf("%f+%fi\n", c.real, c.imagine);
	
	d = DodawanieWskaznik(&a, &b);
	printf("%f+%fi\n", d->real, d->imagine);
	
	free(d);
	return 0;
}

