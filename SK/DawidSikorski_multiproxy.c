/* Definicja potrzebna do POLLRDHUP */
#define  _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>

#include<sys/socket.h>
#include<netinet/tcp.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <netdb.h>

#include<errno.h>

int TworzGniazdo(unsigned int);
struct pollfd *DodajPolaczenie(int, struct pollfd *,unsigned int , struct addrinfo *);
struct pollfd *UsunPolaczenie(struct pollfd *, unsigned int , unsigned int, unsigned int);
void zamknij(struct pollfd *Klienci, unsigned int ilosc_polaczen){
	unsigned int i;
	/* Zamykamy wszystkie gniazda */
	for(i = 0; i < ilosc_polaczen; i+=2){
		close(Klienci[i].fd);
	}
	free(Klienci);
}
int main(int argc, char *argv[]){
	unsigned int i;
	if(argc < 2){
		printf("Zla ilosc argumentow!\nProsze uzywac: %s local_port_1:host_1:host_port_1 [local_port_2:host_2:host_port_2 ...]\n", argv[0]);
		return 1;
	}
	for(i = 1; i < argc; i++){
		if(fork()==0){
			/* Deklarujemy zmienne potrzebne do oblsugi sieci */
			int gniazdo;
			struct addrinfo *informacje;
			unsigned int port;
			unsigned int ilosc_polaczen;
			char adres_docelowy[100];
			char port_docelowy[5];
			struct pollfd *Klienci;
			char bufor[10000];
			int ilosc_znakow;
			
			/* Zapisujemy z ktorego i na ktory port bedziemy przesylac pakiety oraz adres docelowy */
			sscanf(argv[i], "%u:%[^:]:%s", &port, adres_docelowy, port_docelowy);
			
			/* Pobieramy informacje o hoscie docelowym */
			if (getaddrinfo(adres_docelowy, port_docelowy, NULL, &informacje) < 0) {
                printf("Blad pobierania informacji o adresie!\n");
                exit(1);
            }
			/* Tworzymy gniazdo na odpowieni port */
			gniazdo = TworzGniazdo(port);
			
			/* Tworzymy tablice polaczen */
			ilosc_polaczen = 1;
			Klienci = malloc(sizeof(struct pollfd) * ilosc_polaczen);
			/* Ustawiamy 1 klienta jako nasze gniazdo. Ustawanimy na odbior danych i utrate polaczenia */
			Klienci[0].fd = gniazdo;
			Klienci[0].events = POLLIN | POLLRDHUP;
			
			while(1){
				/* Sprawdzamy czy jest jakis ruch siociowy z timeout'em na 5 minut*/
				if(poll(Klienci, ilosc_polaczen, 300000) < 0){
					printf("Brak ruchu sieciowego!\n");
					/* Wywolujemy funkcje czyszczace */
					zamknij(Klienci, ilosc_polaczen);
					exit(1);
				}
				/* Sprawdzamy dla ktorego polaczanie cos przyszlo */
				for(i = 0; i < ilosc_polaczen; i++){
					/* Jezeli na i'tym nic nie zwrocono to pomijamy */
					if(Klienci[i].revents == 0){
						continue;
					}
					/* Sprawdzamy czy przyszly jakies dane */
					if((Klienci[i].revents & POLLIN) == POLLIN){
						/* Jezeli przyszly pakiety do nas, tworzymy polaczenie do przesylania */
						if(Klienci[i].fd == gniazdo){
							Klienci = DodajPolaczenie(gniazdo, Klienci, ilosc_polaczen, informacje);
							ilosc_polaczen += 2;
						} else {
							errno = 0;
							/* W przeciwnym wypadku pobieramy dane */
							if((ilosc_znakow = recv(Klienci[i].fd, bufor, 1024, 0)) < 0){
								if(errno == EAGAIN){
									Klienci[i].revents = 0;
									continue;
								} else {
									printf("Blad pobierania danych!\n");
									/* Wywolujemy funkcje czyszczace */
									zamknij(Klienci, ilosc_polaczen);
									exit(1);
								}
							}
							/* Dodajemy znak konca napisu */
							bufor[ilosc_znakow] = '\0';
							/* Wysylamy odpowiednio do docelowego lub zrodlowego */
							if(i % 2 == 0){
								send(Klienci[i - 1].fd, bufor, ilosc_znakow, 0);
							} else {
								send(Klienci[i + 1].fd, bufor, ilosc_znakow, 0);
							}
						}
					}
					/* Sprawdzamy czy polaczenie zostalo zakonczne */
					if((Klienci[i].revents & POLLRDHUP) == POLLRDHUP){
						/* Zamykamy odpoweidnio docelowy i zrodlowy host */
						close(Klienci[i].fd);
						if(i % 2 == 0){
							close(Klienci[i - 1].fd);
							Klienci = UsunPolaczenie(Klienci, ilosc_polaczen, i, i - 1);
						} else {
							close(Klienci[i + 1].fd);
							Klienci = UsunPolaczenie(Klienci, ilosc_polaczen, i, i + 1);
							/* Pomijamy nastepne polaczenie w zbiorze */
							i++;
						}
						ilosc_polaczen -= 2;
						continue;
					}
					/* Ustawiamy na brak ruchu */
					Klienci[i].revents = 0;
				}
            }
			/* Wywolujemy funkcje czyszczace */
			zamknij(Klienci, ilosc_polaczen);
			exit(0);
		}
	}
	for(i = 1; i < argc; i++){
		/* Czekamy na wszystkicj potomkow, zeby nie pozostaly procesy */
		wait(NULL);
	}
    return 0;
}

int TworzGniazdo(unsigned int port){
	struct sockaddr_in serwer;
	int gniazdo, otwarte = 1;
	/* Tworzymy gniazdo */
	if((gniazdo = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printf("Nie mozna stowrzyc gniazda!\n");
		exit(1);
	}
	/* Ustawiamy wszystkie bity na 0 */
	bzero(&serwer, sizeof(serwer));
	/* Ustawiamy odpowiedni port i rodzine */
	serwer.sin_family = AF_INET;
	serwer.sin_port = htons(port);
	serwer.sin_addr.s_addr = htonl(INADDR_ANY);
	/* Ustawiamy na wersje nieblokujaca */
	if (ioctl(gniazdo, FIONBIO, (char *) &otwarte) == -1) {
        printf("Nie ustawiono na nieblokujaca!\n");
		/* Zamykamy gniazdo */
		close(gniazdo);
        exit(1);
    }
	/* Przypisujemy gniazdu odpowienie parametry */
	if (bind(gniazdo, (struct sockaddr *) &serwer, sizeof(serwer)) < 0) {
        printf("Blad bindowania gniazda!\n");
		/* Zamykamy gniazdo */
		close(gniazdo);
        exit(1);
    }
	/* Ustawiamy gniazdo do nasluchu */
	listen(gniazdo, SOMAXCONN);
	return gniazdo;
}

struct pollfd *DodajPolaczenie(int gniazdo, struct pollfd *Klienci,unsigned int ilosc_polaczen, struct addrinfo *docelowy) {
	int otwarte = 1, kontrol;
	struct sockaddr_in adres_klienta;
	struct addrinfo *zrodlowy;
	/* Ustawiamy wszystkie bity na 0 dla adresu docelowego*/
	bzero(&adres_klienta, sizeof(adres_klienta));
	socklen_t dlugosc_adresu_klienta = sizeof(adres_klienta);
	/* Rozszerzamy baze polaczanych klientow o zroblowy i docelowy */
	Klienci = realloc(Klienci, sizeof(struct pollfd) * (ilosc_polaczen + 2));
	/* Ustawiamy pierwszy jako zrodlowy */
    Klienci[ilosc_polaczen].events = POLLIN | POLLRDHUP;
    Klienci[ilosc_polaczen + 1].events = POLLIN | POLLRDHUP;
	/* Sprawdzmy czy polaczenie bedzie dostepne */
	if ((Klienci[ilosc_polaczen].fd = accept(gniazdo,(struct sockaddr *) &adres_klienta,&dlugosc_adresu_klienta)) < 0) {
        printf("Nie zaakceptowano polaczenia!\n");
		/* Wywolujemy funkcje czyszczace */
		zamknij(Klienci, ilosc_polaczen);
        exit(1);
    }
	/* Tworzymy gniazdo przez ktore bedziemy wysylac do docelowego */
    if ((Klienci[ilosc_polaczen + 1].fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Blad tworzenia gniazda!\n");
		/* Wywolujemy funkcje czyszczace */
		zamknij(Klienci, ilosc_polaczen);
        exit(1);
    }
	/* Probujemy nawiazac polaczenie */
	kontrol = -1;
	zrodlowy = docelowy;
	while(docelowy != NULL){
		kontrol = connect(Klienci[ilosc_polaczen + 1].fd, docelowy->ai_addr, docelowy->ai_addrlen);
		if(kontrol == -1){
			docelowy = docelowy->ai_next;
		} else {
			break;
		}
	}
	docelowy = zrodlowy;
	if(kontrol == -1){
		printf("Brak polaczenia z hostem docelowym!\n");
		/* Wywolujemy funkcje czyszczace */
		zamknij(Klienci, ilosc_polaczen);
		exit(1);
	}
	/* Ustawiamy na wersje nieblokujaca */
    if (ioctl(Klienci[ilosc_polaczen + 1].fd, FIONBIO, (char *) &otwarte) == -1) {
        printf("Nie ustawiono na nieblokujaca!\n");
		/* Wywolujemy funkcje czyszczace */
		zamknij(Klienci, ilosc_polaczen);
        exit(1);
    }

    return Klienci;
}
struct pollfd *UsunPolaczenie(struct pollfd *Klienci, unsigned int ilosc_polaczen, unsigned int ktory, unsigned int ktory_2) {
    unsigned int i, j;
	/* Tworzymy nowa tablice klientow do ktorej bedziemy przepisywac wszystkie polaczenia bez zakonczonego */
	struct pollfd *Klienci_2 = malloc((ilosc_polaczen - 2) * sizeof(struct pollfd));
    /* Przepisujemy potrzebne informacje */
	for (i = 0, j = 0; i < ilosc_polaczen; i++, j++) {
        /* Jezeli jest do usuniacia pomijamy */
		if (i == ktory || i == ktory_2){
			j--;
            continue;
		}
		/* Informacje o uchwytach i eventach/odpowiedziach */
        Klienci_2[j].fd = Klienci[i].fd;
        Klienci_2[j].revents = Klienci[i].revents;
        Klienci_2[j].events = Klienci[i].events;
    }
	/* Zwalniamy pamiec zajmowana przez aktualych klientow */
    free(Klienci);
	/* Zwracamy zbior pomiejszony o zbedne polaczenie */
    return Klienci_2;
}