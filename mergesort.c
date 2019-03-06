#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define pprintf(f_, ...) printf(("\033[38;5;%um"f_"\e[0m"),30+(unsigned int)pthread_self()%255,##__VA_ARGS__) 


int largoArreglo(int * arre){
	int len=sizeof(arre)/sizeof(int);
	printf("\n%d\n",len);
	return len;
}

/*
int * dividir(){
	
	
}
*/

int arreglo[4]={3,5,6,2};//pruebita, luego lo hago de longitud random y lleno de randoms >:c

int main(){
	int len=sizeof(arreglo)/sizeof(int);
	printf(" largo %d \n",len);
	
	//dividir(arreglo, 0, fin)
	printf(" laargoo %d \n",largoArreglo(arreglo));
	

}






