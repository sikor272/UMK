#include <stdio.h>
int main(int argc, char **argv)
{
	if(argc<2){
		printf("Brak parametru\n");
		return 0;
	}
	printf("Witaj %s\n", argv[1]);
	return 0;
}

