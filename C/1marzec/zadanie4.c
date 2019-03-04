
#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned long long int czas;
	scanf("%llu", &czas);
	printf(" %llu sekund to %llu lat\n", czas ,czas / ( 60 * 60 * 24 * 12 * 7 * 4));
	printf(" %llu sekund to %llu miesiecy\n", czas ,czas / ( 60 * 60 * 24 * 7 * 4));
	printf(" %llu sekund to %llu tygodni\n", czas ,czas / ( 60 * 60 * 24 * 7));
	printf(" %llu sekund to %llu dni\n", czas ,czas / ( 60 * 60 * 24));
	printf(" %llu sekund to %llu godzin\n", czas ,czas / ( 60 * 60 ));
	printf(" %llu sekund to %llu minut\n", czas ,czas / 60);
	printf(" %llu sekund to %llu sekund\n", czas ,czas);
	return 0;
}

