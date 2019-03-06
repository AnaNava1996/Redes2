#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)//argc cuantos argumentos se le van a pasar
{	
	int idSocket,port,idCanal,validarListen;
	//SECCION DE CONFIGURACION
	idSocket = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in servidor;
	struct sockaddr_in cliente;

	//Paso 1: Creación del socket usando AF_INET
	if (idSocket == -1)
	{
		perror("Error al crear el socket");
		exit(EXIT_FAILURE);
	}
	//Paso numero 2 llenamos la estructura del servidor y después publicamos el servicio

	memset(&servidor,sizeof(servidor), 0);
	port = atoi(argv[1]);
	//Reinicializando la estructura
	//Puertos no deben de ser menor a 1024 
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons ( port );//¿casteo a tipo puerto?
	//INADDR asigna la interfaz de red por default
	servidor.sin_addr.s_addr = INADDR_ANY;

	int bind = bind(idSocket,servidor,sizeof(servidor));
	if (bind == -1)
	{
		perror("Error en el bind");
		exit(EXIT_FAILURE);
	}

	validarListen = listen(idSocket,2);//servidor bloqueante (que atiende una conección a la vez), va encolar 2
	if (validarListen == -1 )
	{
		perror("Error al validar listen");
		exit(EXIT_FAILURE);
	}
	int tam = sizeof(cliente);
	idCanal = accept(idSocket,&cliente,&tam);
	if (idCanal == -1)
	{
		printf("Error en el canal\n");
		exit(EXIT_FAILURE);
	}
	// Comienza fase de comunicación

	char buffer[50];
	int nCar = recv(idCanal,buffer,50,0);
	buffer[nCar] = '\0';
	printf("Mensaje recibido del cliente: %s\n",buffer);
	strcpy(buffer,'Hola');
	nCar = send(idCanal,buffer,strlen(buffer),0);
	close(idCanal);

	return 0;
}
