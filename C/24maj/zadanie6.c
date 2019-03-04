#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int *tab,i;
	
	tab = malloc(20 * sizeof(int));
	
	for(i = 0; i < 20; i++){
		*(tab + i) = i;
	}
	for(i = 0; i < 20; i += 2){
		*(tab + i) *= 3;
	}
	
	for(i = 0; i < 20; i++){
		printf("%d ", *(tab + i));
	}
	return 0;
}

