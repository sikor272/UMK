#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n,*tab,*i,j;
	scanf("%d", &n);
	tab = malloc(n * sizeof(int));
	for(i = tab, j = 0; i < tab + n; i++, j++){
		*i = j;
	}

	for(i = tab; i < tab + n; i += 2){
		*i *= 3;
	}

	for(i = tab; i < tab + n; i++){
		printf("%d ", *i);
	}

	free(tab);
	return 0;
}

