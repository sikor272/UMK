#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char **argv)
{
	int losowa,user;
	srand(time(NULL));
	losowa = rand() % 15 + 1;
	scanf("%i",&user);
	while(user != losowa){
		if(user > losowa){
			printf("Za duza\n");
		}
		if(user < losowa){
			printf("Za mala\n");
		}
		scanf("%i",&user);
	}
	printf("Gratulacje zgadles!\n");
	return 0;
}

