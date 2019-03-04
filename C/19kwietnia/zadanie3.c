#include <stdio.h>

void silnia_rek(int num, int *wynik){
	if(num < 2){
		*wynik = 1;
		return;
	}
	silnia_rek(num - 1, wynik);
	(*wynik) = (*wynik) * num;
}

void silnia_iter(int num, int *wynik){
	int i;
	
	*wynik = 1;
	for(i = 2; i <= num; i++){
		(*wynik) = (*wynik) * i;
	}
	return;
}


int main(int argc, char **argv)
{
	int s;
	silnia_iter(10, &s);
	printf("%d\n", s);
	
	silnia_rek(9, &s);
	printf("%d\n", s);
	
	return 0;
}

