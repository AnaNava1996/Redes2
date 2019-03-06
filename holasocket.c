#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>


int main(int argc, char **argv){
	//crear al socket
	int idSocket, port, idCanal;
	puerto= atoi(argv[1]);
	
	//PASO 1: creación de socket
	struct sockaddr_in servidor;//ahi vamos a guardar la dir ip y puerto del servidor
	struct sockaddr_in cliente;
	
	idSocket = socket (AF_INET,SOCK_STREAM,0);
	
	//el bind se hace con sockaddr_in....
	if(idSocket == -1){
		perror("Error al crear el socket");
		exit(EXIT_FAILURE);
	}
	//PASO 2: llenamos la estructura del servidor y despues publicamos el servicio
	//Reinicializando la estructura
	memset(&servidor, sizeof(servidor),0);
	//un puerto menor a 1024 no porque esos están reservados... los demás los podríamos usar pero hay que ver 
	//cuales usan las otras aplicaciones... mysql usa no se cual etc
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons( puerto );
	
	
	if(validarListen == -1){
		perror("Error al validar listen");
		exit(EXIT_FAILURE);
	}

	//       int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
	int tam = sizeof(cliente);
	idCanal = accept(idSocket,&cliente,&tam);//accept devuelve el identificador del canal
	
	if(idCanal == -1){
		printf("Error en el canal\n");
		exit(EXIT_FAILURE);
	}
	
	char buffer[50];
	int nCar = recv(idCanal,buffer,50,0);
	buffer[nCar]='\0';
	printf("Mensaje recibido del cliente: %s\n",buffer);
	nCar = 
	
	
	return 0;
}





//el servidor tiene una cola, donde se guardan las peticiones... si solo tengo una cola de tamaño 3, la 4 peticion que llegue se va a perder








