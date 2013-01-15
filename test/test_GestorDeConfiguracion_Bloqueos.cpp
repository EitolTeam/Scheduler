/*
 ============================================================================
 Author      : Hector
 Description : Prueba de la clase gestor de configuracion.
 	 	 	   La explicación grafica de este ejemplo la puede encontrar en
 	 	 	   doc/Bloqueo.pdf

 ============================================================================
 */


#include <gtkmm/main.h>
#include "GestorDeConfiguracion.h"
#include "Proceso.h"


int main (int argc, char *argv[])
{
	Bloqueo bloqueo1(1,2,1);
	Bloqueo bloqueo2(2,2,1);
	Bloqueo bloqueo3(1,2,2);

	GestorDeConfiguracion::addBloqueo(bloqueo1);
	GestorDeConfiguracion::addBloqueo(bloqueo2);
	GestorDeConfiguracion::addBloqueo(bloqueo3);

	int cantElementos=GestorDeConfiguracion::getCantidadDeBloqueos();

	printf("Ahora hay %d elementos en el fichero \n", cantElementos);

	vector<Bloqueo>* listaDeBloqueos=GestorDeConfiguracion::getBloqueos();

	printf("lista.size()=%d\n",unsigned(listaDeBloqueos->size()));

	vector<Bloqueo>* listaDeBloqueosFiltrados=GestorDeConfiguracion::getBloqueos(1);
	cantElementos=listaDeBloqueosFiltrados->size();
	printf("Hay %d elementos en el fichero del proceso %d\n", cantElementos,1);

	delete listaDeBloqueosFiltrados;
	listaDeBloqueosFiltrados=GestorDeConfiguracion::getBloqueos(2);
	cantElementos=listaDeBloqueosFiltrados->size();
	printf("Hay %d elementos en el fichero del proceso %d\n", cantElementos,2);

	delete listaDeBloqueosFiltrados;
	listaDeBloqueosFiltrados=GestorDeConfiguracion::getBloqueos(3);
	cantElementos=listaDeBloqueosFiltrados->size();
	printf("Hay %d elementos en el fichero del proceso %d\n", cantElementos,3);

	delete listaDeBloqueosFiltrados;
	listaDeBloqueosFiltrados=GestorDeConfiguracion::getBloqueos(4);
	cantElementos=listaDeBloqueosFiltrados->size();
	printf("Hay %d elementos en el fichero del proceso %d\n", cantElementos,4);

	delete listaDeBloqueos;
	delete listaDeBloqueosFiltrados;
}
