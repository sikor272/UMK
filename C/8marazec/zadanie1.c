#include <stdio.h>
void parzyste(int a, int b)
{
	if(a % 2 == 1)
		a++;
	while(a <= b)
	{
		printf("%d ",a);
		a += 2;
	}
	return;
}
int main(int argc, char **argv)
{
	int a,b;
	if(argc < 3){
		perror("Brak parametrow!\n");
		return -1;
	}
	sscanf(argv[1],"%d", &a);
	sscanf(argv[2],"%d", &b);
	parzyste(a, b);
	return 0;
}

