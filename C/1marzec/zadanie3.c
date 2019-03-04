
#include <stdio.h>

int main(int argc, char **argv)
{
	int n;
	int i;
	scanf("%d",&n);
	// 1 sposob
	for(i = 0; i < n - 1; i++)
	{
		printf("%d butelki oranzady staly na plocie, o %d butelki! Jesli jedna zrzucimy zostanie %d!\n", n - i, n  - i , n - i - 1); 
	}
	printf("1 butelka oranzady stala na plocie, o 1 butelka! Jesli jedna zrzucimy nie zostanie zadna!\n");
	// 2 sposob
	i = n;
	while(i > 1)
	{
		printf("%d butelki oranzady staly na plocie, o %d butelki! Jesli jedna zrzucimy zostanie %d!\n", i, i, i - 1);
		i--; 
	}
	printf("1 butelka oranzady stala na plocie, o 1 butelka! Jesli jedna zrzucimy nie zostanie zadna!\n");
	// 3 sposob
	i = n;
	do{
		printf("%d butelki oranzady staly na plocie, o %d butelki! Jesli jedna zrzucimy zostanie %d!\n", i, i, i - 1);
		i--; 
	}while(i > 1);
	printf("1 butelka oranzady stala na plocie, o 1 butelka! Jesli jedna zrzucimy nie zostanie zadna!\n");
	return 0;
}

