#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char **argv)
{
	int j, d, i;
	char linia[200];
	char wynik[50*200];
	i = 0;
	while(1){
		scanf("%s",linia);
		d = strlen(linia);
		if(!strncmp(linia, "STOP", 4)){
			break;
		}
		for(j = 0; j < d; j++){
			wynik[i] = linia[j];
			i++;
		}
		wynik[i] = ' ';
		i++;
	}
	printf("%c",wynik[0]);
	for(j = 1; j < i; j++){
		if(wynik[j] == ' '){
			j++;
		}
		if(!isalnum(wynik[j - 1]) && !isalnum(wynik[j])){
			printf("\n");
		} else if(isalpha(wynik[j - 1]) && !isalpha(wynik[j])){
			printf("\n");
		} else if(!isalpha(wynik[j - 1]) && isalpha(wynik[j])){
			printf("\n");
		} else if(!isdigit(wynik[j - 1]) && isdigit(wynik[j])){
			printf("\n");
		} else if(isalnum(wynik[j - 1]) && !isalnum(wynik[j])){
			printf("\n");
		}
		printf("%c",wynik[j]);
	}
	return 0;
}
