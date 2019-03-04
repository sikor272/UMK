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
#include<sys/wait.h>
int ilosc = 0;
int gniazdo;
void koniec(int signal){
	printf("Koncze, dostalem %d wiadomosci.\n", ilosc);
	close(gniazdo);
	exit(0);
}
void zombie(int signal){
	while(waitpid(-1,NULL,WNOHANG)>0);
}
void zlicz(int signal){
	ilosc++;	
}
int main(int argc,char *argv[]){
	int nowy;
	char bufor[1000];
	struct sockaddr_in serwer,client;
	int glowny;
	int bytes;
	socklen_t dlugosc;
	signal(SIGINT,koniec);
	signal(SIGCHLD,zombie);
	signal(SIGTSTP,zlicz);
	if(argc != 1){
		printf("Za malo argumentow!\nProsze uzywac: %s", argv[1]);
		exit(1);
	}
	glowny = getpid();
	gniazdo = socket(AF_INET, SOCK_STREAM, 0);
	dlugosc = sizeof(client);
	serwer.sin_family = AF_INET;
	serwer.sin_port = htons(8888);
	serwer.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(gniazdo,(struct sockaddr*)&serwer,sizeof(serwer));
	listen(gniazdo, 10);
	printf("Czekam na klientow...\n");
	while(1){
			nowy = accept(gniazdo,(struct sockaddr*)&client,&dlugosc);
			if(fork()==0){
				while(1){
					bytes = read(nowy,bufor,1000);
				bufor[bytes]='\0';
					if(strcmp("<koniec>",bufor)==0){
			close(nowy);
			exit(0);
		}
				printf("[%d]:Wiadomosc od IP %s, port %d: %s\n",getpid(), inet_ntoa(client.sin_addr), ntohs(client.sin_port), bufor);
				for(int i = 0; i < strlen(bufor);i++){
					bufor[i] = toupper(bufor[i]);	
				}
				printf("Odsylam: %s\n",bufor);
				write(nowy,bufor,strlen(bufor));
					kill(glowny,SIGTSTP);
						}
			}
			
	}
	close(gniazdo);
	return 0;	
}