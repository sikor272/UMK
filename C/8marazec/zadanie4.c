#include <stdio.h>

int main(int argc, char **argv)
{
	int min, max, n;
	int i;
	sscanf(argv[1], "%i", &min);
	max = min;
	for(i = 2; i < argc; i++)
	{
		sscanf(argv[i],"%i", &n);
		if(n > max)
		{
			max = n;
		}
		if(n < min)
		{
			min = n;
		}
	}
	printf("Min: %i \nMax: %i \n", min, max);
	return 0;
}

