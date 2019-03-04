#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/reg.h>
#include <time.h>

const int long_size = sizeof(long);
/* Deklaracja funckji, obsluga na dole programu */
void pobierz_dane(char *napis, long dlugosc, pid_t pid_dziecko, long adres);
void wyslij_dane(char *napis, long dlugosc, pid_t pid_dziecko, long adres);
void zamiana_znakow(char *napis);

int main(){
    srand(time(NULL));
    /* Zmienna do przechowywania id procesu dziecka */
    pid_t pid_dziecko;
    /* Zmienna do przechwycenia procesu dziecka */
    int dziecko;
    /* Zmienne do przechowywania informacji o obszarze pamieci procesu dziecka oraz dlugosci danych */
    long adres;
    long dlugosc;
    /* Zmienna do przechowywania przechwyconych danych */
    char *napis;
	int kontrola = 1;

    /* Tworzymy proces dziecka */
    if((pid_dziecko = fork()) == 0){
        /* Uzyskujemy bit sledzenia */
        ptrace(PTRACE_TRACEME, NULL, NULL, NULL);
        /* Wywolujemy proces ktory bedziemy sledzic */
        execl("/bin/ls", "ls", NULL);
    } else {
        /* W prociecie ojca przechwytujemy sygnaly wysylane przec proces dziecka */
        while(1){
            /* Poszukujemy procesu potomka */
            wait(&dziecko);
            /* Sprawdzamy czy proces dziecka nadal wysyla sygnaly */
            if(WIFEXITED(dziecko)){
                /* Jezeli nie dostajemy sygnalu, konczymy */
                break;
            }
			/* Jezeli potomek wyslal sygnal pisania, zaczynamy zamiane danych */
			if (ptrace(PTRACE_PEEKUSER, pid_dziecko, long_size * ORIG_RAX, NULL) == SYS_write){
				/* Sprawdzamy czy wywolanie jest nieparzyste, ze wszgedu na podwojna ilosc wykonan */
				if(kontrola){
					kontrola = 0;
					/* Pobieramy adres oraz dlugosc danych wysylanych przez proces potomka */
					adres = ptrace(PTRACE_PEEKUSER, pid_dziecko, long_size * RSI, NULL);
					dlugosc = ptrace(PTRACE_PEEKUSER, pid_dziecko, long_size * RDX, NULL);
					/* Deklarujemy miejsce potrzebne na dane */
					napis = malloc(sizeof(char) * (dlugosc + 1));
					/* Pobieramy dane wypisywane przez potomka */
					pobierz_dane(napis, dlugosc, pid_dziecko, adres);
					/* Wywolujemy funkcje zmieniajaca napis */
					zamiana_znakow(napis);
					/* Wysylamy dane do potomka */
					wyslij_dane(napis, dlugosc, pid_dziecko, adres);
				} else {
					kontrola = 1;
				}
				
			}
            /* Wysylamy procesowi potomnemu sygnal, aby wykonal operacje */
            ptrace(PTRACE_SYSCALL, pid_dziecko, NULL, NULL);
        }
    }
    return 0;
}

void pobierz_dane(char *napis, long dlugosc, pid_t pid_dziecko, long adres){
	long wartosc, i;
	/* Czytamy po kilka znakow */
	for(i = 0; i < dlugosc; i += long_size){
		/* Pobieramy znaki */
		wartosc = ptrace(PTRACE_PEEKDATA, pid_dziecko, adres + i, NULL);
		/* Zapisyjemy do napisu pobrane dane, rzutujac na chara */
		memcpy(napis + i, (char *) &wartosc, long_size);
	}
	/* Jezeli zostaly nam jeszcze jakies znaki pobieramy je */
	if(dlugosc % long_size){
		/* Pobieramy znaki */
		wartosc = ptrace(PTRACE_PEEKDATA, pid_dziecko, adres + i, NULL);
		/* Zapisyjemy do napisu pobrane dane, rzutujac na chara */
		memcpy(napis + i * 4, (char *) &wartosc, dlugosc % long_size);
	}
	/* Dodajemy znak konca napisu */
    napis[dlugosc] = '\0';
	return;
}
void wyslij_dane(char *napis, long dlugosc, pid_t pid_dziecko, long adres){
	long wartosc, i;
	/* Wysylamy po kilka znakow */
	for(i = 0; i < dlugosc; i += long_size){
		/* Rzutujemy znaki na liczby */
		memcpy((char *) &wartosc, napis + i, long_size);
		/* Wysylamy dane */
		ptrace(PTRACE_POKEDATA, pid_dziecko, adres + i, wartosc);
	}
	/* Jezeli zostaly nam jeszcze jakies znaki wysylamy je */
	if(dlugosc % long_size){
		/* Rzutujemy znaki na liczby */
		memcpy((char *) &wartosc, napis + i, long_size);
		/* Wysylamy dane */
		ptrace(PTRACE_POKEDATA, pid_dziecko, adres + i * 4, wartosc);
	}
	return;
}
void zamiana_znakow(char *napis){
	int i;
	printf("%s\n",napis);
	for(i = 0; i < strlen(napis)-1; i++){
		napis[i] = (char)(rand() % 95 + 32);
	}
	return;
}
