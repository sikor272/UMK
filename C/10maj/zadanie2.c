#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n,*tab,*i,*j,a;
	
	if(argc < 2){
		fprintf(stderr, "Brak parametru");
		return -1;
	}
	sscanf(argv[1], "%d", &n);
	n++;
	
	tab = malloc(n * sizeof(int));
	
	*tab = 0;
	*(tab + 1) = 0;
	for(i = tab + 2, a = 2; i < tab + n; i++, a++){
		*i = a;
	}
	
	for(i = tab; i < tab + n; i++){
		if(*i > 0){
			for(j = i + *i; j < tab + n; j += *i){
				*j = 0;
			}
		}
	}
	
	for(i = tab, a = 0; i < tab + n; i++, a++){
		if(*i != 0){
			printf("%d ", *i);
		}
	}
	
	free(tab);
	return 0;
}

