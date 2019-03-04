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
	int bytes;
	int polacz;
	struct sockaddr_in serwer,client;
	if(argc != 2){
		printf("Za malo argumentow!\nProsze uzywac: %s IP_serwera", argv[1]);
		exit(1);
	}
	gniazdo = socket(AF_INET, SOCK_STREAM, 0);
	dlugosc = sizeof(serwer);
	client.sin_family = AF_INET;
	client.sin_port = htons(0);
	client.sin_addr.s_addr = htons(0);
	
	serwer.sin_family = AF_INET;
	serwer.sin_port = htons(8888);
	serwer.sin_addr.s_addr = (inet_addr(argv[1]));
	polacz = connect(gniazdo,(struct sockaddr*)&serwer,sizeof(serwer));
	printf("Podaj wiadomosc do serwera:\n");
	while(1){
		printf("> ");
	b = bufor;
	znaki = getline(&b,&ilosc,stdin);
	bufor[strlen(bufor) - 1] = '\0';
	bytes = write(gniazdo,bufor,strlen(bufor));
		if(strcmp("<koniec>",bufor)==0){
			close(gniazdo);
			exit(0);
		}
	printf("Odpowiedz serwera:\n");
	bytes = read(gniazdo,bufor,1000);
				bufor[bytes]='\0';
	printf("%s\n",bufor);
	}
	close(gniazdo);
	return 0;	
}