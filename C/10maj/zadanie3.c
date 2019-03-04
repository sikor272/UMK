#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n,**tab,**tac,**tak,i,p,j,k;
	
	if(argc < 2){
		fprintf(stderr, "Brak parametru");
		return -1;
	}
	sscanf(argv[1], "%d", &n);
	
	tab = malloc(n * sizeof(int*));
	tac = malloc(n * sizeof(int*));
	tak = malloc(n * sizeof(int*));
	
	for(i = 0; i < n; i++){
		*(tab + i) = malloc(n * sizeof(int));
		*(tac + i) = malloc(n * sizeof(int));
		*(tak + i) = malloc(n * sizeof(int));
	}
	
	p = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			*(*(tab + i) + j) = p;
			p += 2;
		}
	}
	
	k = 1;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			*(*(tac + i) + j) = k;
			k += 2;
		}
	}
	
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			*(*(tak + i) + j) = *(*(tab + i) + j) + *(*(tac + i) + j);
		}
	}
	
	
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%d ", *(*(tab + i) + j));
		}
		printf("   ");
		for(j = 0; j < n; j++){
			printf("%d ", *(*(tac + i) + j));
		}
		printf("   ");
		for(j = 0; j < n; j++){
			printf("%d ", *(*(tak + i) + j));
		}
		printf("\n");
	}
	
	
	for(i = 0; i < n; i++){
		free(*(tab + i));
		free(*(tac + i));
		free(*(tak + i));
	}
	free(tab);
	free(tac);
	free(tak);
	return 0;
}

