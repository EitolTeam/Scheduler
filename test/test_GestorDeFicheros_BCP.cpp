/*
 ============================================================================
 Author      : Hector
 Description : Prueba de la clase gestor de ficheros.
 	 	 	   Escribe y rescata ESTRUCTURAS de un fichero
 ============================================================================
 */


#include <gtkmm/main.h>
#include "GestorDeFicheros.h"
#include "Proceso.h"
#include <string.h>

int main (int argc, char *argv[])
{

	printf("Inicia\n");

	GestorDeFichero<Proceso::BCP> gestor("Procesos.conf");

	Proceso::BCP bcp;

	// Escribe 3 estruturas BCP en el fichero
	for (int i = 1; i <= 3; ++i) {
		bcp.pid=bcp.ppid=bcp.idControl=bcp.instanteDeLlegada=i;
		bcp.tipoDeProceso=Proceso::BCP::TipoDeProceso(i-1);
		printf("Escribe %d \n",i);
		gestor.add(bcp);
	}

	printf("-------------------------------------\n");

	// Cantidad de elementos en el fichero
	int cantElementos=gestor.getCantElem();

	printf("Ahora hay %d elementos en el fichero \n", cantElementos);


	// Lee todos las estructuras del fichero
	for (int i = 0; i < cantElementos ; ++i) {
		bcp=gestor.get(i);
		printf("\nRescató BCP={\n");
		printf("  id %d\n",bcp.pid);
		printf("  pid %d\n}",bcp.pid);
	}
}
