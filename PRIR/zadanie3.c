#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
void* update(void *ptr){
	int *a = malloc(sizeof(int));
	*a = 11;
	return a;
}
int main(){
	pthread_t thread1;
	void* wynik;	
	pthread_create(&thread1, NULL, &update,NULL);
	pthread_join(thread1,&wynik);
	printf("%d\n", *(int*)wynik);
	free(wynik);
	return EXIT_SUCCESS;
}
