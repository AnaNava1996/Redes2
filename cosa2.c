#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include<linux/unistd.h>
#include<sys/syscall.h>


void* myFunction(void*);

int main(){

	/* Paso 1: Creación del hilo */
	pthread_t*  firstThread;
	int x;
	int f;
	//char *msg[]={"hilo1","hilo2","hilo3","hilo4","hilo5"};
	

	printf("Numero de hilos : ");
	scanf("%d", &x);

	firstThread = malloc( sizeof(pthread_t) * x); //

	for (int i = 0; i < x; ++i) {
		f = pthread_create(&firstThread[i], NULL, myFunction, &firstThread[i]);
		printf("El padre %u creo al hilo %p\n" , (unsigned int)pthread_self(),   &firstThread[i]  );
		if(f == -1){
			printf("Error al crear el hilo");
			exit(1);
		}
	}

	for (int i = 0; i < x; ++i) {
		pthread_join(firstThread[i],NULL);
		free(&firstThread[i]);
	}

	return 0;
}

void* myFunction(void* a){

	pthread_t* b = (pthread_t *) a;
	unsigned int c = (unsigned int)pthread_self();
	printf("Hola Mundo desde el hilo %p id %u\n", b,c);
	//retorna_id_hilo(c);
	pthread_exit(NULL);

}

