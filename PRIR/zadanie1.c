#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	int a = 2;
	pid_t child = fork();
	if(child == 0){
		a = 4;
		printf("%d\n", a);
	}else{
		wait(&child);
		printf("%d\n", a);
	}
	return EXIT_SUCCESS;
}