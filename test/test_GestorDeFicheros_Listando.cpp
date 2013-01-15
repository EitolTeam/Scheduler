/*
 ============================================================================
 Author      : Hector
 Description : Prueba de la clase gestor de ficheros.
 	 	 	   Rescata ESTRUCTURAS de un fichero con el metodo getLista()
 ============================================================================
 */


#include <gtkmm/main.h>
#include "GestorDeFicheros.h"
#include "Proceso.h"

int main (int argc, char *argv[])
{


	GestorDeFichero<Proceso::BCP> gestor("Procesos.cfg");

	// Cantidad de elementos en el fichero
	int cantElementos=gestor.getCantElem();

	printf("Ahora hay %d elementos en el fichero \n", cantElementos);

	Proceso::BCP bcp;

	vector<Proceso::BCP> *lista=gestor.getLista();

	printf("lista.size()=%d",unsigned(lista->size()));

}
