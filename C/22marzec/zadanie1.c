#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct napis {
    char *str;
    unsigned int len;
    int powtorzenia;
};
int rosnacy(char *napis, int size){
	int i;
	for(i = 1; i < size; i++){
		if(napis[i] <= napis[i-1]){
			return 0;
		}
	}
	return 1;
}
int pierwsza(char *napis, int size){
	int i, suma;
	suma = 0;
	for(i = 0; i < size; i++){
		suma += napis[i];
	}
	for(i = 2; i * i <= suma; i++){
		if(suma % i == 0){
			return 0;
		}
	}
	return 1;
}
int main(int argc, char **argv)
{
	FILE *plik;
	int ilosc, i, j, rosnie, powtorz, pierwsz;
	struct napis *tablica;
	
	if((plik = fopen("napisy.txt","r")) == NULL){
		perror("Nie moge otworzyc pliku z danymi");
    	return -1;
	}
	
	fscanf(plik,"%i",&ilosc);
	tablica = malloc(ilosc * sizeof(struct napis));
	
	for(i = 0; i < ilosc; i++){
		fscanf(plik,"%u",&tablica[i].len);
		tablica[i].str = malloc(tablica[i].len + 1);
		fscanf(plik,"%s",tablica[i].str);
		tablica[i].powtorzenia = 0;
	}
	
	rosnie = 0;
	printf("Napisy rosnace:\n");
	for(i = 0; i < ilosc; i++){
		if(rosnacy(tablica[i].str,tablica[i].len)){
			rosnie++;
			printf("%s\n",tablica[i].str);
		}
	}
	printf("Ilosc : %i\n",rosnie);
	
	powtorz = 0;
	for(i = ilosc - 1; i >= 0; i--){
		for(j = i - 1; j >= 0; j--){
			if(tablica[i].powtorzenia < 0){
				break;
			}
			if(!strcmp(tablica[i].str,tablica[j].str)){
				tablica[i].powtorzenia++;
				tablica[j].powtorzenia--;
				if(tablica[i].powtorzenia == 1){
					powtorz++;
				}
			}
		}
	}
	printf("Ilosc powtarzajacych sie: %i\n",powtorz);	
	printf("Napisy powtarzajace sie:\n");
	for(i = 0; i < ilosc; i++){
		if(tablica[i].powtorzenia > 0){
			printf("%s %i\n",tablica[i].str, tablica[i].powtorzenia + 1);
			powtorz++;
		}
	}

	
	pierwsz = 0;
	for(i = 0; i < ilosc; i++){
		if(pierwsza(tablica[i].str,tablica[i].len)){
			pierwsz++;
		}
	}
	printf("Ilosc wyrazow pierwszych: %i\n",pierwsz);
	
	fclose(plik);
	free(tablica);
	return 0;
}

