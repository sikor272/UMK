/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "nfs.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

void
nfs_1(char *host)
{
	CLIENT *clnt;
	pliczek  *result_1;
	polacz  start_1_arg;
	zwroc  *result_2;
	pobieranie  pull_1_arg;
	wyslij  push_1_arg;
	int  *result_3, *result_4, koniec_1_arg, wyslane = 0, plik_edycja;
	char bufor[65536], linia[1024], edycja[1024], polecenie[2048];
	
	#ifndef	DEBUG
	clnt = clnt_create (host, NFS, NFS_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
	
	#endif	/* DEBUG */
	printf("Polecenie: ");
	scanf("%s", linia);
	if(strcmp(linia,"exit") == 0){
		printf("Zapraszamy ponownie\n");
		exit(0);
	}
	if(strcmp(linia,"clear") == 0){
		system("clear");
		printf("Dostepne polecenie : 'view' 'edit' 'upload' 'download' 'clear' 'exit'\n");
		return;
	}
	/* Ogladanie */
	if(strcmp(linia,"view") == 0){
		printf("Plik: ");
		scanf("%s", linia);
		strcpy(start_1_arg.nazwa, "/nfs/");
		strcpy(start_1_arg.nazwa+5, linia);
		start_1_arg.tryb = 2;
		result_1 = start_1(&start_1_arg, clnt);
		if (result_1 == (pliczek *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		if(result_1->plik < 0){
			printf("Brak lub nie mozna otworzyc pliku!\n");
			return;
		}
		pull_1_arg.plik = result_1->plik;
		pull_1_arg.pozycja = 0;
		pull_1_arg.przesun = 0;
		while(1){
			result_2 = pull_1(&pull_1_arg, clnt);
			if(result_2 == (zwroc *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			if(result_2->ilosc == -1){
				printf("Blad pobierania lub przesuniecia!\n");
				koniec_1_arg = result_1->plik;
				result_4 = koniec_1(&koniec_1_arg, clnt);
				if (result_4 == (int *) NULL) {
					clnt_perror (clnt, "call failed");
				}
				exit(1);
			}
			strcpy(bufor + wyslane, result_2->dane);
			wyslane += result_2->ilosc;
			if(result_2->ilosc < 2048)
				break;
		}
		if(wyslane != 0){
			bufor[wyslane - 1] = '\0';
			printf("Zawartosc:\n%s\n", bufor);
		} else {
			bufor[0] = '\0';
			printf("Pusty plik\n");
		}
		koniec_1_arg = result_1->plik;
		result_4 = koniec_1(&koniec_1_arg, clnt);
		if (result_4 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		
	} 
	
	/* Edycja */
	if(strcmp(linia,"edit") == 0){
		printf("Plik: ");
		scanf("%s", linia);
		strcpy(start_1_arg.nazwa, "/nfs/");
		strcpy(start_1_arg.nazwa+5, linia);
		strcpy(edycja, "/tmp/nfs_edycja_");
		strcpy(edycja + 16, linia);
		
		plik_edycja = open(edycja, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		start_1_arg.tryb = 0;
		result_1 = start_1(&start_1_arg, clnt);
		if (result_1 == (pliczek *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		if(result_1->plik < 0){
			printf("Nie mozna otworzyc/utworzyc pliku!\n");
			return;
		}
		pull_1_arg.plik = result_1->plik;
		pull_1_arg.pozycja = 0;
		pull_1_arg.przesun = 0;
		
		if(result_1->pusty == 0){
			while(1){
				result_2 = pull_1(&pull_1_arg, clnt);
				if(result_2 == (zwroc *) NULL) {
					clnt_perror (clnt, "call failed");
				}
				if(result_2->ilosc == -1){
					printf("Blad pobierania lub przesuniecia!\n");
					koniec_1_arg = result_1->plik;
					result_4 = koniec_1(&koniec_1_arg, clnt);
					if (result_4 == (int *) NULL) {
						clnt_perror (clnt, "call failed");
					}
					close(plik_edycja);
					exit(1);
				}
				write(plik_edycja, result_2->dane, result_2->ilosc);
				if(result_2->ilosc < 2048)
					break;
			}
			
			koniec_1_arg = result_1->plik;
			result_4 = koniec_1(&koniec_1_arg, clnt);
			if (result_4 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			start_1_arg.tryb = 1;
			result_1 = start_1(&start_1_arg, clnt);
			if (result_1 == (pliczek *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		}
		close(plik_edycja);
		strcpy(polecenie, "vi ");
		strcpy(polecenie + 3, edycja);
		system(polecenie);
		plik_edycja = open(edycja, O_RDONLY);
		
		push_1_arg.plik = result_1->plik;
		while(1){
			wyslane = read(plik_edycja, push_1_arg.dane, 2047);
			push_1_arg.dane[wyslane] = '\0';
			result_3 = push_1(&push_1_arg, clnt);
			if (result_3 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			if(wyslane < 2047)
				break;
		}
		koniec_1_arg = result_1->plik;
		result_4 = koniec_1(&koniec_1_arg, clnt);
		if (result_4 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		close(plik_edycja);
	} 
	
	/* Pobieranie */
	if(strcmp(linia,"download") == 0){
		printf("Plik: ");
		scanf("%s", linia);
		strcpy(start_1_arg.nazwa, "/nfs/");
		strcpy(start_1_arg.nazwa+5, linia);
		strcpy(edycja, linia);
		
		start_1_arg.tryb = 2;
		result_1 = start_1(&start_1_arg, clnt);
		if (result_1 == (pliczek *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		if(result_1->plik < 0){
			printf("Brak lub nie mozna otworzyc pliku!\n");
			return;
		}
		plik_edycja = open(edycja, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		pull_1_arg.plik = result_1->plik;
		pull_1_arg.pozycja = 0;
		pull_1_arg.przesun = 0;
		
		while(1){
			result_2 = pull_1(&pull_1_arg, clnt);
			if(result_2 == (zwroc *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			if(result_2->ilosc == -1){
				printf("Blad pobierania lub przesuniecia!\n");
				koniec_1_arg = result_1->plik;
				result_4 = koniec_1(&koniec_1_arg, clnt);
				if (result_4 == (int *) NULL) {
					clnt_perror (clnt, "call failed");
				}
				close(plik_edycja);
				exit(1);
			}
			write(plik_edycja, result_2->dane, result_2->ilosc);
			if(result_2->ilosc < 2048)
				break;
		}
		koniec_1_arg = result_1->plik;
		result_4 = koniec_1(&koniec_1_arg, clnt);
		if (result_4 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		close(plik_edycja);
	}
	
	/* Wysylanie */
	if(strcmp(linia,"upload") == 0){
		printf("Plik: ");
		scanf("%s", linia);
		strcpy(start_1_arg.nazwa, "/nfs/");
		strcpy(start_1_arg.nazwa+5, linia);
		strcpy(edycja, linia);
		
		plik_edycja = open(edycja, O_RDONLY);
		if(plik_edycja < 0){
			printf("Nie ma takiego pliku pliku lub brak uprawnien!\n");
			return;
		}
		start_1_arg.tryb = 1;
		result_1 = start_1(&start_1_arg, clnt);
		if (result_1 == (pliczek *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		if(result_1->plik < 0){
			printf("Nie mozna otworzyc/utworzyc pliku lub bledna komenda!\n");
			return;
		}
		push_1_arg.plik = result_1->plik;
		while(1){
			wyslane = read(plik_edycja, push_1_arg.dane, 2047);
			push_1_arg.dane[wyslane] = '\0';
			result_3 = push_1(&push_1_arg, clnt);
			if (result_3 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			if(wyslane < 2047)
				break;
		}
		koniec_1_arg = result_1->plik;
		result_4 = koniec_1(&koniec_1_arg, clnt);
		if (result_4 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		close(plik_edycja);
	} 
	#ifndef	DEBUG
	clnt_destroy (clnt);
	#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	printf("Witaj uzytkowniku na serwerze NFS\n");
	printf("Dostepne polecenie : 'view' 'edit' 'upload' 'download' 'clear' 'exit'\n");
	printf("Domyslny edytor : vi\n");
	host = argv[1];
	while(1){
		nfs_1 (host);
	}
exit (0);
}
