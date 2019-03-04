#include <stdio.h>

void swap(int *a, int *b){
	int c;
	c = *a;
	*a = *b;
	*b = c;
	return; 
}

void sort(int *a, int *b, int *c){
	if(*a < *b){
		if(*b < *c){
			return;
		}
		if(*a < *b){
			swap(b, c);
			return;
		}
		swap(a, c);
		swap(b, c);
		return;
	}
	swap(a, b);
	if(*b < *c){
		return;
	}
	swap(b, c);
	if(*a < *b){
		return;
	}
	swap(a, b);
	return;
}

int main(int argc, char **argv)
{
	int a,b,c;
	a = 1 + (b = (3 * (c = 2)));
	printf("%d %d %d\n", a, b, c);
	sort(&a, &b, &c);
	printf("%d %d %d\n", a, b, c);
	
	return 0;
}

