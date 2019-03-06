#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define pprintf(f_, ...) printf(("\033[38;5;%um"f_"\e[0m"),30+(unsigned int)pthread_self()%255,##__VA_ARGS__) 

typedef struct matriz{
int ini;
int fin;
}mt;

int **matrizA;
int **matrizB;
int NFA,NCA,NFB,NCB;

void *transpuesta(void* arg){
	//pprintf("\nHola soy un hilo\n");
	mt * arre=(mt*)arg;
	for(int i=arre->ini; i<arre->fin; i++){
		for(int j=0; j<NFA ; j++){
			//pprintf("\nHola soy un hilo\n");
			matrizB[i][j]=matrizA[j][i];
			pprintf(" %d ",matrizB[i][j]);
		}
		printf("\n");
	}
	pthread_exit(arre);
}





int main(void){
	int numh,residuo,tareas;
	
	printf("introduzca el num de filas: ");
	scanf("%d",&NFA);
	NCB=NFA;

	printf("\nintroduzca el num de columnas: ");
	scanf("%d",&NCA);
	NFB=NCA;

	printf("\nintroduzca el num de hilos: ");
	scanf("%d",&numh);
	
	residuo=NCA%numh;
	tareas=NCA/numh;

	matrizA=malloc(NFA*sizeof(int*));//creo la matriz A
	for(int i=0;i<NFA;i++){
		matrizA[i]=malloc(NCA*sizeof(int));
	}

	matrizB=malloc(NFB*sizeof(int*));//creo la matriz B
	for(int i=0;i<NCB;i++){
		matrizB[i]=malloc(NCB*sizeof(int));
	}


	for(int i=0; i<NFA; i++){//lleno la matriz A y la imprimo
		for(int j=0; j<NCA; j++){
			matrizA[i][j]=rand()%4;
			printf(" %d ",matrizA[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	/*
	for(int i=0; i<NFA; i++){
		for(int j=0; j<NCA; j++){
			matrizB[j][i]=matrizA[i][j];
		}
	}
	*/
	
/*	
	for(int i=0; i<NFB;i++){
		for(int j=0; j<NCB ; j++){
			printf(" %d ",matrizB[i][j]);
		}
		printf("\n");
	}	
*/

	
	pthread_t *hilos= malloc(numh*sizeof(pthread_t));
	mt *entradas=malloc(numh*sizeof(mt));
	
	for(int i=0; i<numh ; i++){
		if(residuo>0 && (i+1)==numh){
			entradas[i].ini=i*tareas;
			entradas[i].fin=i*tareas+residuo+1;			//le mando la dirección del arreglo...para luego recastearlo en la función
		}															//a lo que originalmente era, es como pasarle la dirección de ese struct,
		else{													// y luego decirle a la función que tome el tamaño de ese struct a partir de esa dirección
			entradas[i].ini=i*tareas;
			entradas[i].fin=i*tareas+(tareas-1)+1;
		}
		pthread_create(&hilos[i],NULL,transpuesta,(void*)&entradas[i]);
	}

	for(int i=0; i<numh ;i++){
		pthread_join(hilos[i],NULL);
	}
		
}





