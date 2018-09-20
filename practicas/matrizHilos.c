#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define pprintf(f_, ...) printf(("\033[38;5;%um"f_"\e[0m"),30+(unsigned int)pthread_self()%255,##__VA_ARGS__) 


typedef struct matricita
{
  int ini,fin;}mt;

void *multiplicacion(void* arg);

int **matrizA;
int **matrizB;
int **matrizC;
int NFA,NCA,NFB,NCB;

int main(void){
	clock_t start_t, end_t, total_t;
	int num,numa,i,j,k,l,nump,tareas,residuo;
 	pid_t pid;
	printf("\nnumero de filas matriz A: ");
	scanf("%d",&NFA);
	printf("\nnumero de columnas A= numero de filas B: ");
	scanf("%d",&NCA);
	NFB=NCA;
	printf("\nnumero de columnas B: ");
	scanf("%d",&NCB);
	nump=NFA+1;
	while(nump>NFA){
		printf("\nnumero de procesos/hilos:\n");
		scanf("%d",&nump);
	}
	tareas=NFA/nump;
	residuo=NFA%nump;
	
	matrizA=malloc(NFA*sizeof(int*));//al numero de filas le doy un numero indeterminado de espacios
	for(i=0;i<NFA;i++){//a cada fila, le doy
    	matrizA[i]=malloc(NCA*sizeof(int));//el numero de columnas que es
    }

	matrizB=malloc(NFB*sizeof(int*));//al numero de filas le doy un numero indeterminado de espacios
    for(i=0;i<NFB;i++){//a cada fila, le doy
    	matrizB[i]=malloc(NCB*sizeof(int));//el numero de columnas que es
    }

	matrizC=malloc(NFA*sizeof(int*));//al numero de filas le doy un numero indeterminado de espacios
    for(i=0;i<NFA;i++){//a cada fila, le doy
    	matrizC[i]=malloc(NCB*sizeof(int));//el numero de columnas que es
    }

     for (i = 0; i < NFA; i++){//lleno la matriz A
        for (j = 0; j < NCA; j++){
          matrizA[i][j]=rand()%(4);
  		  pprintf("matrizA[%d][%d]: %d \n",i,j,matrizA[i][j]);}}
     for (i = 0; i < NFB; i++){//lleno la matriz B
        for (j = 0; j < NCB; j++){
          matrizB[i][j]=rand()%(4);
  		  pprintf("matrizB[%d][%d]: %d \n",i,j,matrizB[i][j]);}}

//pthread_t hilo[nump];
pthread_t *hilo= malloc(nump*sizeof(pthread_t));
//mt arre[nump]; //arreglo de structs
mt *arre= malloc(nump*sizeof(mt));

start_t = clock();
for(i=1;i<=nump;i++){
	if(residuo>0 && i==nump){
		arre[i-1].ini =tareas*(i-1);
		arre[i-1].fin =(tareas*i+residuo)-1;}
	else{
		arre[i-1].ini =tareas*(i-1);
		arre[i-1].fin =(tareas*i)-1;}
	pthread_create(&hilo[i-1],NULL,multiplicacion,(void*)&arre[i-1]);//castearlo como void
}

for(l=0;l<nump;l++){
	pthread_join(hilo[l],(void*)&arre);
	//printf("\narreeee: ini %d fin %d\n",arre->ini,arre->fin);
	for (int l=arre->ini;l<=arre->fin;l++){
		for(int k=0;k<NCA;k++){
			printf(" %d ",matrizC[l][k]);
			}
		printf("\n");
		}
	}

end_t = clock();
double tiempo = (double)(end_t - start_t) /CLOCKS_PER_SEC;//
printf("Tiempo total: %lf\n", tiempo  );

for (int u = 0; u < NFA; u++) {
	free(matrizA[u]);
	}
for (int u = 0; u < NFB; u++) {
	free(matrizB[u]);
	}
for (int u = 0; u < NCA; u++) {
	free(matrizC[u]);
	}
	/*
for (int u = 0; u<nump; u++){
	free(&hilo[i]);
	}*/

}

void *multiplicacion(void * arg){
	mt * arre = (mt *) arg;
	for (int l=arre->ini;l<=arre->fin;l++){
		for(int j=0;j<NCB;j++){
			int numa=0;
			for(int k=0;k<NFB;k++){
				numa+=(matrizA[l][k]*matrizB[k][j]);}
			matrizC[l][j]=numa;
			pprintf("matrizC[%d][%d]=%d\n",l,j,numa);
		}
	}
	pthread_exit(arre);		
}
