#include <stdio.h>

int main(int argc, char **argv)
{
	int tab[2];
	
	tab[200] = 17;
	printf("%d\n", tab[200]);
	return 0;
}

