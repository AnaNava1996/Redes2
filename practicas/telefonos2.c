/*
hacer n productores y m consumidores para x zonas críticas.
productor1 escribe 11111111 z veces
productor2 escribe 22222222 z veces
productor3 escribe 33333333 z veces

... 
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#define pprintf(f_, ...) printf(("\033[38;5;%um"f_"\e[0m"),30+(unsigned int)pthread_self()%255,##__VA_ARGS__) 



void * consumidor(void*);
void * productor(void*);

char secCrit [5][9];
char secCrit2 [5][9];
int idSem;
int consumosT,ns,numHilos,numProductores,numConsumidores,producciones;


void cierre(int numSem){
	struct sembuf sops;
	sops.sem_num=numSem;//numero del semaforo
	sops.sem_op=-1;//operacion
	sops.sem_flg=SEM_UNDO;//máscara de bits
	semop(idSem,&sops,1);//nsops es el numero de operaciones	
}

void apertura(int numSem){
	struct sembuf sops;
	sops.sem_num=numSem;//numero del semaforo
	sops.sem_op=1;//operacion
	sops.sem_flg=SEM_UNDO;//máscara de bits
	semop(idSem,&sops,1);//nsops es el numero de operaciones	
}

void matar_semaforos(int ns){
	for(int i=0; i<ns; i++){
		semctl(idSem,i,IPC_RMID,0);//mato a los semáforos
	}	
}


int main(int argc, char * argv[]){
	/*
	secCrit2=malloc(sizeof(*char)*5);
	for(int p=0;p<5;p++){
		secCrit2[p]=malloc(sizeof(char)*9);
	}*/
	
	//argc es el numero de argumentos
	//argv es el valor del argumento
	// si le paso un entero lo casteo con atoi
	producciones=atoi(argv[1]);//cuanto produce cada hilo
	ns = atoi(argv[2]);//cantidad de semaforos
	numProductores = atoi(argv[3]);
	numConsumidores = atoi(argv[4]);
	numHilos=numProductores+numConsumidores;
	consumosT=producciones*numProductores;//consumos totales para los consumidores
	
	printf("\n%d %d %d %d %d\n",producciones,consumosT, ns, numProductores,numConsumidores);

	secCrit[0][0]='v';
	secCrit[1][0]='v';

	key_t lallave = ftok("/home/Desktop/redes2/practicas",'b');
	idSem =semget(lallave,12,0777 | IPC_CREAT | IPC_EXCL);
	if(idSem==-1){
		idSem = semget(lallave,12,0777);
		if(idSem==-1){
			printf("\nError en ligarse");
			matar_semaforos(ns);
			return(0);
		}
		else{
			semctl(idSem,0,SETVAL,5);//el grandote de la izquierda
			semctl(idSem,1,SETVAL,1);
			semctl(idSem,2,SETVAL,1);
			semctl(idSem,3,SETVAL,1);
			semctl(idSem,4,SETVAL,1);		
			semctl(idSem,5,SETVAL,1);		
			semctl(idSem,6,SETVAL,0);
			semctl(idSem,7,SETVAL,0);
			semctl(idSem,8,SETVAL,0);
			semctl(idSem,9,SETVAL,0);
			semctl(idSem,10,SETVAL,0);
			semctl(idSem,11,SETVAL,2);//el grandote de la derecha
			printf("\ninicia %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d",semctl(idSem,0,GETVAL,NULL),semctl(idSem,1,GETVAL,NULL),semctl(idSem,2,GETVAL,NULL),semctl(idSem,3,GETVAL,NULL),semctl(idSem,4,GETVAL,NULL),semctl(idSem,5,GETVAL,NULL),semctl(idSem,6,GETVAL,NULL),semctl(idSem,7,GETVAL,NULL),semctl(idSem,8,GETVAL,NULL),semctl(idSem,9,GETVAL,NULL),semctl(idSem,10,GETVAL,NULL),semctl(idSem,11,GETVAL,NULL));
		}		
	}
	else{
		semctl(idSem,0,SETVAL,5);//el grandote de la izquierda
		semctl(idSem,1,SETVAL,1);
		semctl(idSem,2,SETVAL,1);
		semctl(idSem,3,SETVAL,1);
		semctl(idSem,4,SETVAL,1);		
		semctl(idSem,5,SETVAL,1);		
		semctl(idSem,6,SETVAL,0);
		semctl(idSem,7,SETVAL,0);
		semctl(idSem,8,SETVAL,0);
		semctl(idSem,9,SETVAL,0);
		semctl(idSem,10,SETVAL,0);
		semctl(idSem,11,SETVAL,2);//el grandote de la derecha
		printf("\ninicia %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d",semctl(idSem,0,GETVAL,NULL),semctl(idSem,1,GETVAL,NULL),semctl(idSem,2,GETVAL,NULL),semctl(idSem,3,GETVAL,NULL),semctl(idSem,4,GETVAL,NULL),semctl(idSem,5,GETVAL,NULL),semctl(idSem,6,GETVAL,NULL),semctl(idSem,7,GETVAL,NULL),semctl(idSem,8,GETVAL,NULL),semctl(idSem,9,GETVAL,NULL),semctl(idSem,10,GETVAL,NULL),semctl(idSem,11,GETVAL,NULL));
	}

	pthread_t hilos[numHilos];
	
	int valors[10]={0,1,2,3,4,5,6,7,8,9};
	
	int prod=0,cons=0;
	for(int i=0 ; i<numProductores ; i++){
		pthread_create(&hilos[i], NULL, productor, (void *)&valors[i]);
		/*if(prod==-1){
			perror("\nError al crear los hilos productores");
			matar_semaforos(ns);
			exit(1);
		}*/	
	}


	for(int i=0 ; i<numConsumidores ; i++){
		pthread_create(&hilos[i+numProductores], NULL, consumidor, (void *)&valors[i]);
		/*
		if(cons==-1){
			perror("\nError al crear los hilos consumidores");
			matar_semaforos(ns);
			exit(1);
		}	
		*/
	}
	

	for (int i =0 ; i<numHilos ;i++){
		pthread_join(hilos[i],NULL);
	}

	matar_semaforos(ns);
	
	return(0);
}

void * productor(void* argv){
	int *arg=(int *)argv;
	char letra=(*arg+1)+'0';
	
	int cont=producciones;
	while(cont!=0){//producciones en la sección crítica
		cierre(0);
		for(int i=0;i<5;i++){
			if(semctl(idSem,i+1,GETVAL,NULL)==1){
				cierre(i+1);//cierro 1 a 5 Sem de productor	
				pprintf("\nP%c    %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d",letra,semctl(idSem,0,GETVAL,NULL),semctl(idSem,1,GETVAL,NULL),semctl(idSem,2,GETVAL,NULL),semctl(idSem,3,GETVAL,NULL),semctl(idSem,4,GETVAL,NULL),semctl(idSem,5,GETVAL,NULL),semctl(idSem,6,GETVAL,NULL),semctl(idSem,7,GETVAL,NULL),semctl(idSem,8,GETVAL,NULL),semctl(idSem,9,GETVAL,NULL),semctl(idSem,10,GETVAL,NULL),semctl(idSem,11,GETVAL,NULL));						
				for(int j=1; j<9 ;j++){
					secCrit[i][j]=letra;	
				}
				secCrit2[i][0]='m';secCrit2[i][1]='e';secCrit2[i][2]='n';secCrit2[i][3]='s';secCrit2[i][4]='a';secCrit2[i][5]='j';secCrit2[i][6]='e';
				secCrit2[i][7]=letra;
				cont=cont-1;
				apertura(i+6);//abro 6 a 10 Sem de consumidor
				break;	
			}
		}
		if(cont==0){	apertura(0);break;	}
		apertura(0);
	}
	printf("\nSoy el productor%c y voy a salir...",letra);
	pthread_exit(NULL);
}

void * consumidor(void * argv){// en el for de aqui no podemos saber cuanto va a consumir cada consumidor... debe ser un ciclo infinito
	int * arg=(int*) argv;
	char letra=(*arg+1)+'0';
	while(consumosT!=0){
		cierre(11);
		for(int i=0;i<5;i++){
			if(semctl(idSem,i+6,GETVAL,NULL)==1){
				cierre(i+6);//cierra de 6 a 10
				printf("\nC%c    %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d",letra,semctl(idSem,0,GETVAL,NULL),semctl(idSem,1,GETVAL,NULL),semctl(idSem,2,GETVAL,NULL),semctl(idSem,3,GETVAL,NULL),semctl(idSem,4,GETVAL,NULL),semctl(idSem,5,GETVAL,NULL),semctl(idSem,6,GETVAL,NULL),semctl(idSem,7,GETVAL,NULL),semctl(idSem,8,GETVAL,NULL),semctl(idSem,9,GETVAL,NULL),semctl(idSem,10,GETVAL,NULL),semctl(idSem,11,GETVAL,NULL));
				printf("\nSoy el consumidor%c y leo:%c%c%c%c%c%c%c%c\n",letra,secCrit[i][1],secCrit[i][2],secCrit[i][3],secCrit[i][4],secCrit[i][5],secCrit[i][6],secCrit[i][7],secCrit[i][8]);
				printf("\nSoy el consumidor%c y leo: %c%c%c%c%c%c%c%c%c\n",letra,secCrit2[i][0],secCrit2[i][1],secCrit2[i][2],secCrit2[i][3],secCrit2[i][4],secCrit2[i][5],secCrit2[i][6],secCrit2[i][7],secCrit2[i][8]);
				consumosT=consumosT-1;
				apertura(i+1);//abre 1 a 5 sem de productor
				break;
			}
		}
		apertura(11);
	}
	printf("\nSoy el consumidor%c y voy a acabar...%d",letra,consumosT);
	pthread_exit(NULL);
}

//	v de vacío
//	l de lleno
//	e de escribiendo
//	r de leyendo



//tarea buscar tipos de errores de semget




