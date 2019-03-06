#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define pprintf(f_, ...) printf(("\033[38;5;%um"f_"\e[0m"),30+(unsigned int)pthread_self()%255,##__VA_ARGS__) 

void *lafuncion(void* arg);



int main(){

char *cadenas[]={"hola","perro","cosa","manzana"};
int num=4;
char *cadena;

char **ap = &cadena;

printf("\n &cadena = %p \n",&cadena);



pthread_t *hilos=malloc(num*sizeof(pthread_t));

for(int i=0; i<num ; i++){
	pthread_create(&hilos[i],NULL,lafuncion,(void*)cadenas[i]);

}

for(int i=0; i<num ;i++){
	pthread_join(hilos[i],(void*)&cadena);
	pprintf("\n%s\n",cadena);
}



}

void *lafuncion( void* arg){
	char * cadena= (char*) arg;
	pprintf("\n%s\n",cadena);
	pthread_exit(cadena);
}





