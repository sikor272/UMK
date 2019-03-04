#include <stdio.h>
unsigned long int silnia_rek(int n)
{
	if(n <= 1)
		return 1;
	else
		return n * silnia_rek(n - 1);
}
unsigned long int silnia_itr(int n)
{
	int silnia = 1;
	while(n > 1)
	{
		silnia *= n;
		n--;
	}
	return silnia;
}
unsigned long int silnia_for(int n)
{
	int silnia = 1, i;
	for(i = 2; i <= n; i++)
	{
		silnia *= i;
	}
	return silnia;
}
int main(int argc, char **argv)
{
	int n;
	if(argc < 2){
		perror("Brak parametru!\n");
		return -1''
	}
	sscanf(argv[1],"%d", &n);
	printf("%lu\n", silnia_itr(n));
	printf("%lu\n", silnia_for(n));
	printf("%lu\n", silnia_rek(n));
	return 0;
}

