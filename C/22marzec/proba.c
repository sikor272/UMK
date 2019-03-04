#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct napis{
	char *str;
	unsigned int len;
	int powtorzenia;
};
int rosnacy(unsigned int size, char *napis){
	int i;
	for(i = 1; i < size; i++){
		if(napis[i - 1] >= napis[i]){
			return 0;
		}
	}
	return 1;
}
int pierwszy(unsigned int size, char *napis){
	int i,suma;
	suma = 0;
	for(i = 0; i < size; i++){
		suma += napis[i];
	}
	if(suma < 2){
		return 0;
	}
	for(i = 2; i * i < suma; i++){
		if(suma % i == 0){
			return 0;
		}
	}
	return 1;
}
int main(int argc, char **argv)
{
	FILE *plik;
	struct napis *dane;
	int i,j,rozmiar,powtorzen,pierwszych,rosnace;
	
	plik = fopen("napisy.txt", "r");
	if(plik == NULL){
		perror("Nie udalo sie otworzyc pliku z danymi!");
		return -1;
	}
	
	fscanf(plik, "%i", &rozmiar);
	dane = malloc(rozmiar * sizeof(struct napis));
	
	for(i = 0; i < rozmiar; i++){
		fscanf(plik, "%u", &dane[i].len);
		dane[i].str = malloc((dane[i].len + 1) * sizeof(char));
		fscanf(plik, "%s", dane[i].str);
		dane[i].powtorzenia = 0;
	}
	
	rosnace = 0;
	printf("Napisy rosnace:\n");
	for(i = 0; i < rozmiar; i++){
		if(rosnacy(dane[i].len, dane[i].str)){
			printf("%s\n", dane[i].str);
			rosnace++;
		}
	}
	printf("Ilosc napisow rosnacych: %i\n", rosnace);
	
	for(i = 0; i < rozmiar; i++){
		for(j = i + 1; j < rozmiar; j++){
			if(!strcmp(dane[i].str,dane[j].str)){
				dane[i].powtorzenia++;
				dane[j].powtorzenia--;
			}
		}
	}
	
	powtorzen = 0;
	printf("Napisy powtarzajace sie:\n");
	for(i = 0; i < rozmiar; i++){
		if(dane[i].powtorzenia > 0){
			printf("%s\n", dane[i].str);
			powtorzen++;
		} else {
			dane[i].powtorzenia = 0;
		}
	}
	printf("Ilosc napisow powtarzajacych sie: %i\n", powtorzen);
	
	pierwszych = 0;
	for(i = 0; i < rozmiar; i++){
		if(pierwszy(dane[i].len, dane[i].str)){
			pierwszych++;
		}
	}
	printf("Ilosc napisow pierwszych: %i\n", pierwszych);
	return 0;
}

