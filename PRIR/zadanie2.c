#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
void* update(void *ptr){
	int *a = (int*)ptr;
	*a = 4;
	printf("%d\n",*a);
	return NULL;
}
int main(){
	pthread_t thread1;
	int a = 2;
	
	pthread_create(&thread1, NULL, &update,(void*)&a);
	pthread_join(thread1,NULL);
	
	printf("%d\n", a);
	return EXIT_SUCCESS;
}
