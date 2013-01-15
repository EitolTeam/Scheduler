/*
 ============================================================================
 Author      : Hector
 Description : Prueba de la clase gestor de ficheros.
 	 	 	   Escribe y rescata enteros de un fichero
 ============================================================================
 */


#include <gtkmm/main.h>
#include "GestorDeFicheros.h"
#include <list>
#include "Proceso.h"
#include "GestorDeConfiguracion.h"


int main (int argc, char *argv[])
{
	GestorDeConfiguracion gestorDeConf;
	vector<Proceso> *listaDeProcesos=gestorDeConf.getProcesos();


}
