#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
void* print_messade_function(void *ptr){
	char *message;
	message = (char*)ptr;
	printf("%s\n",message);
	return NULL;
}
int main(){
	pthread_t thread1,thread2;
	char *message1 = "Hello";
	char *message2 = "World";
	pthread_create(&thread1, NULL, &print_messade_function,(void*)message1);
	pthread_create(&thread2, NULL, &print_messade_function,(void*)message2);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return EXIT_SUCCESS;
}