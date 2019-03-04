#include <stdio.h>

int fib(int n){
    int f = 0; 
    int f0 = 1;
    int f1 = 1;
    while (n > 1) {
        n--;
        f = f0 +f1;
        f0 = f1;
        f1 = f;
    }
    return f;
}

int main(void){
    int i;
    for(i =0; i < 8; i++){ 
         printf("fib(%d) = %d\n", i, fib(i));
    } 
    return 0;
}
