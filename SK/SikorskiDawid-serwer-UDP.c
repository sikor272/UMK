#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>
#include<ctype.h>
#include<arpa/inet.h>
int ilosc = 0;
int gniazdo;
void koniec(int signal){
	printf("Koncze, dostalem %d wiadomosci.\n", ilosc);
	close(gniazdo);
	exit(0);
}

int main(int argc,char *argv[]){
	
	char bufor[1000];
	struct sockaddr_in serwer,client;
	socklen_t dlugosc;
	signal(SIGINT,koniec);
	if(argc != 1){
		printf("Za malo argumentow!\nProsze uzywac: %s", argv[1]);
		exit(1);
	}
	gniazdo = socket(AF_INET, SOCK_DGRAM, 0);
	dlugosc = sizeof(client);
	serwer.sin_family = AF_INET;
	serwer.sin_port = htons(8888);
	serwer.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(gniazdo,(struct sockaddr*)&serwer,sizeof(serwer));
	printf("Czekam na klientow...\n");
	while(1){
			recvfrom(gniazdo,&bufor,sizeof(bufor),0,(struct sockaddr*)&client,&dlugosc);
			printf("Wiadomosc od IP %s, port %d: %s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), bufor);
			for(int i = 0; i < strlen(bufor);i++){
				bufor[i] = toupper(bufor[i]);	
			}
			printf("Odsylam: %s\n",bufor);
			sendto(gniazdo,bufor,sizeof(bufor),0,(struct sockaddr*)&client,sizeof(client));
			ilosc++;
	}
	return 0;	
}