#include <stdio.h>
#include <stdlib.h>
 
struct ulamek{
	int licznik;
	int mianownik;
};
int main()
{
	int n;
	struct ulamek *liczba;
	scanf("%d",&n);
	liczba = malloc(n*sizeof(struct ulamek));
	free(liczba);
	return 0;
}
