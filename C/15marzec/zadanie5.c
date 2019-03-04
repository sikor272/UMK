#include <stdio.h>
#include <stdlib.h>
struct wyniki{
	char wojewodztwo[50];
	int osob;
	int procent;
};
int compare(const void * a, const void * b)
{
	struct wyniki *x = (struct wyniki *)a;
	struct wyniki *y = (struct wyniki *)b;
	int zdal_a, zdal_b;
	zdal_a = x->osob * x->procent / 100;
	zdal_b = y->osob * y->procent / 100;
	return zdal_b-zdal_a;
}
int compare_v2(const void * a, const void * b)
{
	struct wyniki *x = (struct wyniki *)a;
	struct wyniki *y = (struct wyniki *)b;
	int zdal_a, zdal_b;
	zdal_a = x->osob;
	zdal_b = y->osob;
	return zdal_b-zdal_a;
}
int main(int argc, char **argv)
{
	struct wyniki tablica[16];
	char linia[50];
	int i, j;
	FILE *plik,*plik2;
	plik = fopen("matury.txt", "r");
	plik2 = fopen("posortowane.txt", "w");
	if (plik == NULL){
		perror("Nie moge otworzyc pliku z danymi");
		return 	-1;
	}
	i = 0;
	while(fgets(linia,50,plik)){
		sscanf(linia,"%s %i %i%%",tablica[i].wojewodztwo,&tablica[i].osob,&tablica[i].procent);
		i++;
	}
	qsort(tablica,i,sizeof(struct wyniki),compare);
	for(j = 0; j < i; j++){
		printf("%s %i %i\n",tablica[j].wojewodztwo,tablica[j].osob,tablica[j].procent);
	}
	printf("\nNajwiecej zdalo w wojewodztwie: %s\n",tablica[0].wojewodztwo);
	printf("\nNajmniej zdalo w wojewodztwie: %s\n",tablica[i-1].wojewodztwo);
	qsort(tablica,i,sizeof(struct wyniki),compare_v2);
	for(j = 0; j < i; j++){
		fprintf(plik2,"%s %i %i\n",tablica[j].wojewodztwo,tablica[j].osob,tablica[j].procent);
	}
	fclose(plik);
	fclose(plik2);
	return 0;
}

