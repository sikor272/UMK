#include <stdio.h>

#define SGN(X) (((X) > 0 ) ? (1) : (((X) < 0) ? (-1) : (0)))
#define MIN(X, Y) ((X) > (Y) ? (X) : (Y))

int main(int argc, char **argv)
{
	printf("%d\n", SGN(13-15*65/100));
	printf("%d\n", MIN(13 - 15 * 65 / 100, 5*12 + 89));
	return 0;
}

