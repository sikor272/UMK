#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
int main(int argc,char *argv[]){
	int gniazdo;
	char bufor[1000];
	char *b;
	size_t znaki;
	size_t ilosc = 1000;
	socklen_t dlugosc;
	
	struct sockaddr_in serwer,client;
	if(argc != 2){
		printf("Za malo argumentow!\nProsze uzywac: %s IP_serwera", argv[1]);
		exit(1);
	}
	gniazdo = socket(AF_INET, SOCK_DGRAM, 0);
	dlugosc = sizeof(serwer);
	client.sin_family = AF_INET;
	client.sin_port = htons(0);
	client.sin_addr.s_addr = htons(0);
	
	serwer.sin_family = AF_INET;
	serwer.sin_port = htons(8888);
	serwer.sin_addr.s_addr = (inet_addr(argv[1]));
	bind(gniazdo,(struct sockaddr*)&client,sizeof(client));
	printf("Podaj wiadomosc do serwera:\n> ");
	b = bufor;
	znaki = getline(&b,&ilosc,stdin);
	bufor[strlen(bufor) - 1] = '\0';
	sendto(gniazdo,bufor,sizeof(bufor),0,(struct sockaddr*)&serwer,sizeof(serwer));
	printf("Odpowiedz serwera:\n");
	recvfrom(gniazdo,&bufor,sizeof(bufor),0,(struct sockaddr*)&client,&dlugosc);
	printf("%s\n",bufor);
	close(gniazdo);
	return 0;	
}