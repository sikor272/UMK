#include <stdio.h>
#include <math.h>
#include <float.h>
 int silnia(int n, int suma)
{
	int wartosc;
	wartosc = suma * (n + 1);
	if(wartosc < suma)
		return n;
	return silnia(n + 1, suma * (n + 1));
}
unsigned int silnia2(unsigned int n, unsigned int suma)
{
	unsigned int wartosc;
	wartosc = suma * (n + 1);
	if(wartosc < suma)
		return n;
	return silnia2(n + 1, suma * (n + 1));
}
 long int silnia3(long int n, long int suma)
{
	long int wartosc;
	wartosc = suma * (n + 1);
	if(wartosc < suma)
		return n;
	return silnia3(n + 1, suma * (n + 1));
}
unsigned long int silnia4(unsigned long int n, unsigned long int suma)
{
	unsigned long int wartosc;
	wartosc = suma * (n + 1);
	if(wartosc < suma)
		return n;
	return silnia4(n + 1, suma * (n + 1));
}
float silnik(float n, float suma)
{
	float wartosc = suma * (n + 1);
	if(wartosc < suma || isinf(wartosc))
	{
		return n;
	}
	return silnik(n + 1, suma * (n + 1));
}
double silnik2(double n, double suma)
{
	double wartosc;
	wartosc = suma * (n + 1);
	if(wartosc < suma || isinf(wartosc))
		return n;
	return silnik2(n + 1, suma * (n + 1));
}
int main(int argc, char **argv)
{
	printf("%i \n",silnia(1, 1));
	printf("%u \n",silnia2(1, 1));
	printf("%li \n",silnia3(1, 1));
	printf("%lu \n",silnia4(1, 1));
	printf("%f \n",silnik(1, 1));
	printf("%f \n",silnik2(1, 1));
	return 0;
}

