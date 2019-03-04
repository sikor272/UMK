#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
struct my_msg{
    char name[16];
	char text[1000];
};
int main(int argc, char *argv[]) {
	int sockfd;
	struct sockaddr_in server_addr, client_addr, *docelowy;
	struct addrinfo *informacje;
	struct my_msg sms, sms_2;
	socklen_t len;
	int child;
	
	if(argc < 2 || argc > 3){
		printf("Error: Prosze uzywac %s adres_maszyny_zdalnej [nick]\n", argv[0]);
		return 1;
	}
	/* Zapisujemy nick uzytkownika */
	if(argc == 2){
		strcpy(sms.name,"NN");
	} else {
		if(strlen(argv[2]) > 15){
			printf("Twoj nick '%s' jest za dlugi!\nMaksymalnie 15 znakow!\n", argv[2]);
			return 1;
		}
		strcpy(sms.name, argv[2]);
	}
	/* Pobieramy informacje o adresie podanego hosta */
	if (getaddrinfo(argv[1], "5272", NULL, &informacje) != 0) {
		printf("Podano bledny adres maszyny!\n");
		return 1;
	}
	/* Tworzymy gniazdo UDP */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		printf("Blad tworzenia gniazda!\n");
		return 1;
	}
	/* Zapamietujemy IP z ktorym bedizemy sie laczyc */
	docelowy = (struct sockaddr_in *)(informacje->ai_addr);
	/* Uzupelniamy strukture naszego serwera */
	server_addr.sin_family	    = AF_INET;           /* IPv4 */
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* Nasz dowolny interfejs */
	server_addr.sin_port        = htons(5272);    /* port serwera */
	/* Uzupelniamy strukture naszego clienta z ktorym sie laczymy */
	client_addr.sin_family	    = AF_INET;           /* IPv4 */
	client_addr.sin_addr 		= docelowy->sin_addr; /* IP docelowego hosta */
	client_addr.sin_port        = htons(5272);    /* port hosta */
	len = sizeof(client_addr);
	/* Rejestrujemy nasze gniazdo w systemie */
	if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		printf("Blad bindowania gniazda!\n");
		printf("Ktos juz uzywa czatu z tej maszyny :(\n");
		close(sockfd);
		return 1;
	}
	printf("Rozpoczynam czat z %s. Napisz <koniec> by zakonczyc czat.\n", inet_ntoa(docelowy->sin_addr));
	/* Wysylamy wiadomosc poczatkowa o naszym dolaczeniu do czatu */
	strcpy(sms.text, "<poczatek>");
	if(sendto(sockfd, &sms, sizeof(sms), 0,(struct sockaddr *)&client_addr, sizeof(client_addr)) < 0){
		printf("Blad wysylania wiadmosci o dolaczeniu!\n");
		close(sockfd);
		return 1;
	}
	/* Tworzymy potomka ktory bedzie odpowiedzalny za wypisywanie odebranych wiadomosci */
	if((child = fork())==0){
		while(1) {
			if(recvfrom(sockfd, &sms_2, sizeof(sms_2), 0, (struct sockaddr *)&client_addr, &len) < 0){
				printf("Blad pobierania wiadomosc!\n");
				return 1;
			}
			/* Jezeli przyszedl nowy uzytkownik informujemy o dolaczeniu */
			if(strcmp(sms_2.text,"<poczatek>") == 0){
				printf("\n[%s (%s) dolaczyl do rozmowy]\n", sms_2.name, inet_ntoa(client_addr.sin_addr));
			} else /* Jezeli odszedl polaczony uzytkownik informujemy o odejsciu */
			if(strcmp(sms_2.text,"<koniec>") == 0){
				printf("\n[%s (%s) zakonczyl rozmowe]\n", sms_2.name, inet_ntoa(client_addr.sin_addr));
			} else { /* W pozostalych przypadkach wypisujemy otrzymana wiadomosc */
				printf("\n[%s (%s)]: %s\n", sms_2.name, inet_ntoa(client_addr.sin_addr), sms_2.text);
			}
			/* W celu estetyki i funkcjonalnosci wypisujemy nasza nazwe */
			printf("[%s]> ", sms.name);
			/* Zeby nadpisywanie sie udalo */
			fflush(stdout);
		}
		close(sockfd);
		exit(0);
	} else {
		while(1) {
			/* Proces macierzysty odpowiada za wysylanie wiadomosci */
			printf("[%s]> ", sms.name);
			fgets(sms.text, 1000, stdin);
			sms.text[strlen(sms.text)-1] = '\0';
			if(sendto(sockfd, &sms, sizeof(sms), 0,(struct sockaddr *)&client_addr, sizeof(client_addr)) < 0){
				printf("Blad wysylania wiadmosci!\n");
				close(sockfd);
				return 1;
			}
			/* Jezeli konczymy wysylamy wiadomosc, zamykamy proces potomny oraz deskrypror i konczymy */
			if(strcmp(sms.text,"<koniec>") == 0){
				if(kill(child, SIGINT) < 0){
					printf("Nie zamknieto potomka!\n");
					close(sockfd);
					return 1;
				}
				close(sockfd);
				return 0;
			}
		}
	}
	return 0;

}
