#include <stdio.h>
#include <string.h>
int bindec(char *binar)
{
	int suma = 0, koniec = strlen(binar) - 1;
	int i;
	for(i = koniec; i >= 0; i--)
	{
		if(binar[koniec - i] == '1')
		{
			 suma |=  1 << i;
		}
	}
	return suma;
}
int main(int argc, char **argv)
{
	char bin[32];
	int liczba;
	int m;
	scanf("%s",bin);
	liczba = bindec(bin);
	printf("%i\n",liczba);
	m = 1 << 2 | 1 << 4;
	if((liczba & m) == m){
		printf("Trzeci i piaty zapalony\n");
	} else {
		printf("Trzeci i piaty zgaszony\n");
	}
	if((liczba & 1 << 2) || (liczba & 1 << 4)){
		printf("Trzeci lub piaty zapalony\n");
	} else {
		printf("Trzeci i piaty zgaszony\n");
	}
	if(liczba & 1 << 2){
		printf("Trzeci zapalony %i\n", liczba);
	} else {
		printf("Trzeci zapalony %i\n", liczba | 1 << 2);
	}
	printf("Liczba po wylaczeniu ostatniego bitu %i\n", (liczba >> 1) << 1);
	printf("Liczba *8 %i\n", liczba << 3);
	printf("Liczba /4 %i\n", liczba >> 2);
	return 0;
}

