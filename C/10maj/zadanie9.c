#include <stdio.h>

int main(void){
    char *c, txt[] = "Paella!";
    c = &txt[3];
    while (2 == 2){
        if (*c-- == 'e')
            break;
    }
    printf("%s\n", c);
    /* Wynik to "aella!" Bo operujemy na wskazniku chara wiec nadal odczytujemy pozostale litery */
    return 0;
}
