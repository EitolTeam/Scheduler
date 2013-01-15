/*
 ============================================================================
 Author      : Hector
 Description : Prueba de la clase gestor de ficheros.
 	 	 	   Escribe y rescata enteros de un fichero
 ============================================================================
 */


#include <gtkmm/main.h>
#include "GestorDeFicheros.h"


int main (int argc, char *argv[])
{
	printf("Inicia\n");

	GestorDeFichero<int> gestor("fichero.cfg");

	// Escribe 3 numeros en el fichero
	for (int i = 0; i < 3; ++i) {
		printf("Escribe %d \n",i);
		gestor.add(i);
	}

	printf("-------------------------------------\n");

	// Cantidad de elementos en el fichero
	int cantElementos=gestor.getCantElem();

	printf("Ahora hay %d elementos en el fichero \n", cantElementos);



	// Lee todos los numeros del fichero
	for (int i = 0; i < cantElementos ; ++i) {
		printf("Rescató %d \n",gestor.get(i));
	}
}
