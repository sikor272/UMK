#include <stdio.h>
#include <string.h>

int zamiana(char *binarka){
	int i,liczba,koniec;
	liczba = 0;
	koniec = strlen(binarka) - 1;
	for(i = 0; i <= koniec; i++){
		if(binarka[i] == '1'){
			liczba |= 1 << (koniec - i);
		}
	}
	return liczba;
}
int main(){
	char binarka[20];
	int liczba,maska;
	scanf("%s", binarka);
	liczba = zamiana(binarka);
	printf("%i\n", liczba);
	
	maska = 1 << 2 | 1 << 4;
	if((liczba & maska) == maska){
		printf("3 i 5 bit jest wlaczony\n");
	}
	
	if(liczba & maska){
		printf("3 lub 5 bit jest wlaczony\n");
	}
	
	printf("Po wlaczeniu 3 bitu: %i\n", liczba | 1 << 2);
	
	printf("Po wylaczeniu 1 bitu: %i\n", (liczba >> 1) << 1);
	
	printf("Liczba * 8 : %i\n", liczba << 3);
	
	printf("Liczba / 4 : %i\n", liczba >> 2);
	
	return 0;
}
