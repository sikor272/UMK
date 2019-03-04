#include <stdio.h>
int main(int argc, char **argv)
{
	unsigned int liczba;
	int i,j;
	scanf("%u",&liczba);
	printf("%x\n",liczba);
	printf("%o\n",liczba);
	j = 0;
	i = 1;
	while(i <= liczba){
		j++;
		i *= 2;
	}
	for(i = j - 1; i >= 0; i--)
	{
		if(liczba & (1 << i)){
			printf("1");
		}
		else
		{
			printf("0");
		}
	}
	return 0;
}

