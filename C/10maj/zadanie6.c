#include <stdio.h>
#define MAX3(X,Y,Z) (((X)>(Y))?(((X)>(Z))?(X):(Z)):(((Y)>(Z))?(Y):(Z)))
#define SGN(X) (((X)>0)?1:(((X)<1)?-1:0))

int main(int argc, char **argv)
{
	printf("%d\n", MAX3(3 + 2, 1 - 5, 6 + 9));
	printf("%d\n", SGN(3 + 2 / 1 - 5 * 6 + 9));
	return 0;
}
