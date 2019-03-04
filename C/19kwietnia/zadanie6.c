#include <stdio.h>
#include <stdlib.h>

void print_bit(int num){
    int i,bit,liczba;
    liczba = num;
    bit = 0;
    while(liczba){
        bit++;
        liczba /= 2;
    }
    for(i = 0; i < bit; i++){
        if(num & (1 << (bit - i - 1))){
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
    return;
}
int set_bit(int num, int bt, int val){
    int i,bit,liczba,value;
    if(val < 0 || val > 1){
        fprintf(stderr, "Zla wartosc bitu");
        exit(-1);
    }
    value = 0;
    liczba = num;
    bit = 0;
    while(liczba){
        bit++;
        liczba /= 2;
    }
    for(i = 0; i < bit; i++){
        if(i == bt){
            if(val == 1){
                value = value | (1 << bt);
            }
        } else {
            if(num & (1 << (bit - i - 1))){
                value = value | (1 << (bit - i - 1));
            }
        }
    }
    if(bt >= bit && val == 1){
        value = value | (1 << bt);
    }
    return value;
}
int flip_bin(int num, int bt){
    int i,bit,liczba,value;
    value = 0;
    liczba = num;
    bit = 0;
    while(liczba){
        bit++;
        liczba /= 2;
    }
    for(i = 0; i < bit; i++){
        if(i == bt){
            if(!(num & (1 << (bit - i - 1)))){
                value = value | (1 << (bit - i - 1));
            }
        } else {
            value = value | (1 << (bit - i - 1));
        }
    }
    return value;
}
int main(int argc, char **argv)
{
	int n;
	scanf("%d", &n);
	print_bit(n);
	n = set_bit(n, 5, 1);
	print_bit(n);
	n = flip_bin(n, 3);
	print_bit(n);
	return 0;
}

