#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define pprintf(f_, ...) printf(("\033[38;5;%um"f_"\e[0m"),30+(unsigned int)pthread_self()%255,##__VA_ARGS__) 


void* myFunction(void*);

int main(){

	/* Paso 1: Creación del hilo */
	pthread_t*  firstThread;
	int x;
	int f;

	printf("Numero de hilos : ");
	scanf("%d", &x);

	firstThread = malloc( sizeof(pthread_t) * x); //

	for (int i = 0; i < x; ++i) {
		f = pthread_create(&firstThread[i], NULL, myFunction, &firstThread[i]);
		pprintf("El padre creo al hilo %p \n", &firstThread[i]);
		if(f == -1){
			printf("Error al crear el hilo");
			exit(1);
		}
	}
	void * hiloid; //
	
	for (int i = 0; i < x; ++i) {
		pthread_join(firstThread[i],&hiloid);
		pprintf("HIJO:%ld\n",*(pthread_t*)hiloid); //
		//free(&firstThread[i]);
	}

	return 0;
}

void* myFunction(void* a){

	pthread_t* b = (pthread_t *) a;
	pprintf("Hola Mundo desde el hilo %p\n", b);
	//pthread_exit(NULL);

	pthread_t* retval = malloc(sizeof(pthread_t)); //
	*retval = pthread_self(); //
	pprintf("Mi hilo:%ld\n",*retval); //
	return (void *) retval; //
}
