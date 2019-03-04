#include <stdio.h>
int main(int argc, char **argv)
{
	char linia[50], wojewodztwo[16][50];
	int osob[16], procenty[16], i, j, suma, zdaly[16], zdalo, max, max_id;
	FILE *plik;
	plik = fopen("matury.txt", "r");
	if (plik == NULL){
		perror("Nie moge otworzyc pliku z danymi");
		return 	-1;
	}
	i = 0;
	suma = 0;
	zdalo = 0;
	max = 0;
	max_id = 0;
	while(fgets(linia,50,plik)){
		sscanf(linia,"%s %i %i%%",wojewodztwo[i],&osob[i],&procenty[i]);
		suma += osob[i];
		zdaly[i] = osob[i] * procenty[i] / 100;
		zdalo += zdaly[i];
		if(zdaly[i] > max){
			max = zdaly[i];
			max_id = i;
		}
		i++;
	}
	printf("Zdawalo %i osob.\n",suma);
	printf("Zdalo %i osob.\n",zdalo);
	printf("W tych wojewodztwach zdawalo ponad 15000 osob:\n");
	for(j = 0; j < i; j++){
		if(osob[j] > 15000){
			printf("%s\n",wojewodztwo[j]);
		}
	}
	printf("W tych wojewodztwach zdawalo mniej niz 70%% osob:\n");
	for(j = 0; j < i; j++){
		if(procenty[j] < 70){
			printf("%s\n",wojewodztwo[j]);
		}
	}
	printf("Najwiecej zdalo w wojewodztwie %s : %i",wojewodztwo[max_id], osob[max_id]);
	fclose(plik);
	return 0;
}

