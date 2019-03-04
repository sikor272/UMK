#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
	int n, s = 0, i;
	char tmp[255];
	
	n = open("liczby.txt", O_RDONLY);
	
	if(n < 0){
		printf("Nie udalo sie otworzyc!\n");
		return -1;
	}
	
	while(read(n, tmp, 255) > 0){
		for(i = 0; i < strlen(tmp); i++){
			if(tmp[i] == '\n'){
				s++;
			}
		}
	}
	
	printf("Wpliku jest %d linii.\n", s);
	close(n);
	return 0;
}

