#include <stdio.h>

void sort(int *a, int *b, int *c){
    int d,e,f;
    d = *a;
    e = *b;
    f = *c;
    if(d < e && d < f){
        if(e > f){
            *c = e;
            *b = f;
        }
        return;
    }
    if(e < f){
        if(d < f){
            *b = d;
        } else {
            *b = f;
            *c = d;
        }
        *a = e;
        return;
    }
    *a = f;
    if(d < e){
        *b = d;
        *c = e;
    } else {
        *c = d;
    }
    return;
}
int main(int argc, char **argv)
{
	int a,b,c;
	a = 1;
	b = 3;
	c = 4;
	sort(&a, &b, &c);
	printf("%d %d %d\n", a, b, c);
	return 0;
}
