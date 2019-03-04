#include <stdio.h>

int main(int argc, char **argv)
{
	int a,b;
	
	a = 7;
	if (a++ > 7) {++a;};
	a = 7;

	a = 7;
	if ((a == 0) && (++a == 8) {a = 0;};
	a = 7;

	a = 0;
	if ((++a) && (--a)) {a = 12;};
	a = 0;
	
	int a = 1;
	if ((a++) || (a == 123)) {a = 12;};
	a = 12;
	
	b = a = 3, a++, a + 3;
	a = 4;
	
	b = (a = 3, a++, a + 3); 
	a = 4;
	return 0;
}

