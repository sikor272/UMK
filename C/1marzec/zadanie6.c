#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	char liczba[255];
	scanf("%s", liczba);
	int n, suma;
	suma = 0;
	n = strlen(liczba);
	int i;
	for(i = 0; i < n; i++)
	{
		suma = suma + (liczba[i] - 48);
	}
	printf("%d\n", suma);
	return 0;
}

