#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
typedef struct _Arg{
	int b;
	int c;
	} Arg;
int a = 2;
void* update(void *arg){
	a = a + ((Arg*)arg)->b;
	a = a * ((Arg*)arg)->c;
	printf("%d\n", a);
	return NULL;
}
int main(){
	Arg arg = {3, 2};
	pthread_t thread1;
	pthread_create(&thread1, NULL, &update,(void*)&arg);
	pthread_join(thread1,NULL);
	printf("%d\n", a);
	return EXIT_SUCCESS;
}
