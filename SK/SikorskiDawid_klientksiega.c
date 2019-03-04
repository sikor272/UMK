#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/sem.h>
#define MY_MSG_SIZE 150

key_t shmkey;
int   shmid;
struct my_data {
    int  typ;
    int login;
	char txt[MY_MSG_SIZE];
} *shared_data;

size_t bufsize = MY_MSG_SIZE;


int main(int argc, char * argv[]) {
	/* Zmienne do przechowywania informacji oraz pomocnicze */
	int semafor;
	int n;
	int ile;
	int i;
	int ktory;
	int wartosc = 0;
	/* Struktura zawierajaca inforacje o pamieci wspoldzielonej */
	struct shmid_ds buf;
	if(argc != 2){
		printf("Error: Niepoprawna ilosc argumentow!\n");
		printf("Prosze uzywac: %s [nazwa pliku zrodlowego serwera].c\n", argv[0]);
		exit(1);
	}
	if((shmkey = ftok(argv[1], 1)) == -1){
		printf("Error: Nie utworzono klucza!\n");
		exit(1);
	}
	printf("Klient ksiegi skarg i wnioskow wita!\n");
	/* Uzyskujemy ades pamieci */
	if( (shmid = shmget(shmkey, 0, 0)) == -1 ) {
		printf("Error: brak dostepu do pamieci lub serwer nie dziala!\n");
		exit(1);
	}
	/* Pobieramy informacje o pamieci */
	if(shmctl(shmid, IPC_STAT, &buf) == -1){
		printf("Error: brak dostepu do inforamcji o pamieci!\n");
		exit(1);
	}
	/* liczymy ile jest rekordow razem */
	ile = buf.shm_segsz / sizeof(struct my_data);
	/* Pobieramy informacje o semaforach */
	if( (semafor = semget(shmkey, 1, 0)) == -1){
		printf("Error: blad semafory!\n");
		exit(1);
	}
	/*Pobieramy adres 1 elementu */
	shared_data = (struct my_data *) shmat(shmid, (void *)0, 0);
	if(shared_data == (struct my_data *)-1) {
		printf("Error: blad wskaznika na pamiec!\n");
		exit(1);
	}
	ktory = -1;
	/* Sprawdzamy ile jest wolnych */
	/* jednoczesnie ktory jest wolnych do pisania */
	for(i = 0; i < ile; i++){
		if((shared_data + i)->typ == 0){
			if((wartosc = semctl(semafor, i, GETVAL)) == -1 ){
				printf("Error: semafor - blad pobierania wartosci!\n");
				exit(1);
			}
			if(wartosc == 1){
				ktory = i;
				if(semctl(semafor, ktory, SETVAL, 0) == -1){
					printf("Error: semafor - nie zablokowano!\n");
					exit(1);
				}
				break;
			}
		}
	}
	/* Sprawdzamy czy jest wolne miejsce */
	if(ktory == -1){
		printf("Brak wolnych wpisow!\n");
		return 0;
	}
	/* Wypisywanie inforamcji o ilosci wolnych wpisow */
	if((ile - ktory) == 1){
		printf("[%d wolny wpis", ile - ktory);
	} else if(((ile - ktory) < 10 || (ile - ktory) > 20) && (ile - ktory) % 10 < 5 && (ile - ktory) % 10 > 1){
		printf("[%d wolne wpisy", ile - ktory);
	} else {
		printf("[%d wolnych wpisow", ile - ktory);
	}	
	printf(" (na %d)]\n", ile);
	
	
	printf("Napisz co ci lezy na watrobie:\n");
	/* Oznaczamy zajety obszar */
	(shared_data + ktory)->typ = 1;
	/* Wczytujemy do pamieci dane */
	n = read(0, (shared_data + ktory)->txt, bufsize);
	/* Dodajemy znak konca napisu */
	(shared_data + ktory)->txt[n-1] = '\0';
	/* Wpisujemy id uzytkownika */
	(shared_data + ktory)->login = getuid();
	printf("Dziekuje za dokonanie wpisu do ksiegi\n");
	
	shmdt(shared_data + ktory);
	/* odbkolowujemy semafor */
	if(semctl(semafor, ktory, SETVAL, 1) == -1){
		printf("Error: semafor - nie odblokowano!\n");
		exit(1);
	}
	return 0;

}

