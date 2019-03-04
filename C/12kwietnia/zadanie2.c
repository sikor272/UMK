#include <stdio.h>
#define SGN(X) (((X) < 0) ? -1 : (((X) > 0) ? 1 : 0))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define AVG(X, Y, Z) (((X) + (Y) + (Z)) / 3)
#define ABS(X) (((X) < 0) ? (-1)*(X) : (X))

int main(int argc, char **argv)
{
	printf("%i\n", SGN(-10));
	printf("%i\n", SGN(0));
	printf("%i\n", SGN(1));
	
	printf("%i\n", MIN(1, 98));
	
	printf("%i\n", MAX(34, 15));
	
	printf("%i\n", AVG(1, 5, 3));
	
	printf("%i\n", ABS(1));
	printf("%i\n", ABS(-10));
	return 0;
}

