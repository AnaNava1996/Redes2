/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */
#include <stdlib.h>
#include "rand.h"


int
main (int argc, char *argv[])
{
  CLIENT *clnt;
  void  *resultado1;
  long semilla;
  double  *resultado2;
  int itera,i;
  char arg;

  //Paso 0: Verificar parametros de recibidos por consola
  if (argc != 4){
    printf("\n\n **** Se requieren 3 parametros 1.- Host 2.- Semilla 3.- Numero de Iteraciones *** \n\n");
    exit(1);
  }

  semilla = (long) argv[2]; // convierte el parametro recibido a un entero largo
  itera = atoi(argv[3]); //convierte el parametro a un entero

  //Paso 1: Incluir el Manejador del cliente (genera un enlace hacia el servicio remoto)
  clnt = clnt_create (argv[1], rand, ver1Rand, "udp");
  if (clnt == NULL) {
    clnt_pcreateerror (argv[1]);
    exit (1);
  }

  //Paso 2: Modificar los esqueletos de la funciones para que realicen la funcionalidad que se les indique

  //Funcion inicializa_random
  resultado1 = inicializa_random_1(&semilla, clnt);
  if (resultado1 ==  NULL) {
    clnt_perror (clnt, "Fallo al realizar la llamada remota 1");
  }

  //funcion obtiene un nuevo numero aleatorio
	
  for(i = 0; i < itera; i++){
    resultado2 = obtiene_nuevo_random_1((void*)&arg, clnt);
    if (resultado2 == (double *) NULL) {
      clnt_perror (clnt, "Fallo al realizar la llamada remota 2");
    }
    else
      printf("\n%d res: %f",i,*resultado2);
  }

  clnt_destroy (clnt);
  exit(0);
}
