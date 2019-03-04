#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/msg.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<pwd.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#define MY_MSG_SIZE 150

/* Zmienne globalne do przechowywania informacji o : */
/* ilosci zajmowanej pamieci, kluczu, semaforze, pamieci wspoldizelonej */
int suma = 0;
int semafor;
key_t shmkey;
int   shmid;
struct my_data {
	int typ;
	int login;
	char txt[MY_MSG_SIZE];
} *shared_data;
/* Obsluga zakonczenia programu */
void sgnhandle(int signal) {
	printf("\n[Serwer]: dostalem SIGINT => koncze i sprzatam...");
	printf(" (odlaczenie: %s, usuniecie: %s, semafory : %s)\n", 
			(shmdt(shared_data) == 0)        ? "OK" : "blad shmdt",
			(shmctl(shmid, IPC_RMID, 0) == 0)? "OK" : "blad shmctl",
			(semctl(semafor, 0, IPC_RMID) == 0)? "OK" : "blad semctl");
	exit(0);
}
/* Obsluga czyszczenia w przypadku bledow */
void blad_semafor(){
	printf("semafory : %s\n", 
			(semctl(semafor, 0, IPC_RMID) == 0)? "OK" : "blad semctl");
}
void blad_dane(){
	printf("odlaczenie: %s\n",(shmdt(shared_data) == 0) ? "OK" : "blad shmdt");
}
void blad_pamiec(){
	printf("usuniecie: %s\n",(shmctl(shmid, IPC_RMID, 0) == 0) ? "OK" : "blad shmctl");
}
/* Obsluga wypisywania */
void sgnhandle2(int signal) {
	int i,ile = 0;
	struct passwd *user;
	/* Pierw sprawdzamy czy cos jest w ksiazce */
	for(i = 0; i < suma; i++){
		/* typ = 1 oznacza ze jest zapisane */
		/* sprawdzamy rowniez czy ktos nadal nie ma dostepu */
		if(shared_data[i].typ != 0 && semctl(semafor, i, GETVAL) != 0){
			ile++;
		}
	}
	if(ile == 0){
		printf("\nKsiega skarg i wnioskow jest jeszcze pusta\n");
		return;
	}
	printf("\n___________  Ksiega skarg i wnioskow:  ___________\n");
	for(i = 0; i < suma; i++){
		/* Jezeli jest cos zapisane oraz nikt nie uzywa aktualnie */
		/* tego obszaru pamieci to wypisujemy */
		if(shared_data[i].typ != 0 && semctl(semafor, i, GETVAL) != 0){
			if((user = getpwuid(shared_data[i].login)) == NULL){
				printf("Error: Blad loginu!\n");
				/* Wywolujemy funkcje czyszczace */
				blad_dane();
				blad_pamiec();
				blad_semafor();
				exit(1);
			} else {
				printf("[%s]", user->pw_name);
			}
			printf(": %s\n", shared_data[i].txt);
		}
	}
}

int main(int argc, char * argv[]) {
	int i;
	/* Struktura zawierajaca inforacje o pamieci wspoldzielonej */
	struct shmid_ds buf;
	if(argc != 3){
		printf("Error: Niepoprawna ilosc argumentow!\n");
		printf("Prosze uzywac: %s [nazwa pliku zrodlowego serwera].c [ilosc wpisow ]\n", argv[0]);
		exit(1);
	}
	/* Zmieniamy napis na liczbe */
	sscanf(argv[2], "%d", &suma);
	
	if(suma < 1 ){
		printf("Error: Zadeklarowano za malo pamieci!\n");
		exit(1);
	}
	/* Obluga sygnalow Ctrl^Z i Ctrl^C */
	signal(SIGINT, sgnhandle);
	signal(SIGTSTP, sgnhandle2);
	
	printf("[Serwer]: ksiega skarg i wnioskow (WARIANT A)\n");
	printf("[Serwer]: tworze klucz...");
	if((shmkey = ftok(argv[1], 1)) == -1){
		printf("Error: Nie utworzono klucza!\n");
		exit(1);
	}
	printf(" OK (klucz: %ld)\n", shmkey);
	
	
	printf("[Serwer]: tworze semafory...");
	if( (semafor = semget(shmkey, suma, 0666 | IPC_CREAT | IPC_EXCL)) == -1){
		printf("Error: blad tworzenia semaforow!\n");
		exit(1);
	}
	printf(" OK\n");
	
	/* Na poczatku blokujemy dostep przez semaforow */
	for(i = 0; i < suma; i++){
		if(semctl(semafor, i, SETVAL, 0) == -1){
			printf("Error: blad nadania wartosci semaforowi nr: %i!\n", i + 1);
			/* Wywolujemy funkcje czyszczaca */
			blad_semafor();
			exit(1);
		}
	}	
	
	printf("[Serwer]: tworze segment pamieci wspolnej dla ksiegi na %d ", suma);
	if(suma == 1){
		printf("wpis...");
	} else if((suma > 20 || suma < 10) && (suma % 10 < 5) && (suma % 10 > 1)){
		printf("wpisy...");
	} else {
		printf("wpisow...");
	}
	
	/* Tworzymy obszar pamieci */
	if( (shmid = shmget(shmkey, suma * sizeof(struct my_data), 0666 | IPC_CREAT | IPC_EXCL)) == -1) {
		printf("Error: blad tworzenia pamieci!\n");
		/* Wywolujemy funkcje czyszczace */
		blad_semafor();
		exit(1);
	}
	/* Pobieramy informacje o pamieci */
	if(shmctl(shmid, IPC_STAT, &buf) == -1){
		printf("Error: blad shmctl!\n");
		/* Wywolujemy funkcje czyszczace */
		blad_pamiec();
		blad_semafor();
		exit(1);
	}
	printf(" OK (id: %d, rozmiar: %zub)\n", shmid, buf.shm_segsz);
	printf("[Serwer]: dolaczam pamiec wspolna...");
	/* Pobieramy adres pierwszego elementu */
	shared_data = (struct my_data *) shmat(shmid, (void *)0, 0);
	if(shared_data == (struct my_data *)-1) {
		printf("Error: blad wskaznika na pamiec!\n");
		/* Wywolujemy funkcje czyszczace */
		blad_pamiec();
		blad_semafor();
		exit(1);
	}
	printf(" OK (adres: %lX)\n", (long int)shared_data);
	for(i = 0; i < suma; i++){
		/* Oznaczamy ze nie ma wiadomosci */
		shared_data[i].typ = 0;
		shared_data[i].login = 0;
		/* Oraz odblokowujemy semafory */
		if(semctl(semafor, i, SETVAL, 1) == -1){
			printf("Error: blad nadania wartosci semaforowi nr: %i!\n", i + 1);
			/* Wywolujemy funkcje czyszczace */
			blad_dane();
			blad_pamiec();
			blad_semafor();
			exit(1);
		}

	}

	printf("[Serwer]: nacisnij Ctrl^Z by wyswietlic stan ksiegi...\n");
	
	while(1){
		/* Serwer jest w trybie czuwania na sygnaly */
		/* dzieki tej funkcji nie robi zbednych obrotow petli */
		/* i tym samym wykoszystujemy mniejsze zasoby */
		pause();
	}	

	return 0;

}

