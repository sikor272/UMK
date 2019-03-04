#include <stdio.h>
#define KWADRAT(X) ((X)*(X))

int main(int argc, char **argv)
{
	int a, b;
	
	printf("%i\n", KWADRAT(2+3)); 
	
	a = 3;
	b = KWADRAT(a++);
	printf("%i\n", b);
	return 0;
}

