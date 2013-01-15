/*
 * GestorDeConfiguracion.cpp
 *
 *  Created on: 31/12/2012
 *      Author: hector
 */

#include "GestorDeConfiguracion.h"
#include "GestorDeFicheros.h"
#include <vector>
#include "Proceso.h"

GestorDeConfiguracion::GestorDeConfiguracion() {

}

vector<Proceso*> * GestorDeConfiguracion::getProcesos() {

	// Para retornar
	vector<Proceso*> *listaFinalDeProcesos=new vector<Proceso*>();

	GestorDeFichero<Proceso::BCP> gestorProc(NOMBRE_FICHERO_DE_PROCESOS);

	// Obtiene los BCP's de el fichero de procesos
	vector<Proceso::BCP> * listaBCP=gestorProc.getLista();

	// Si el fichero esta vacio o no existe
	if (!listaBCP || !listaBCP->size()){
		perror("NO existen procesos declarados en el fichero o este no existe");

		//exit(ENODATA);
		return NULL;
	}

	// Para guardar los bloqueos de un proceso por iteracion
	vector<Bloqueo> * listaBloqueos;

	for (uint i=0 ; i<listaBCP->size() ; ++i ){

		// Se crea el proceso a partir del bcp
		Proceso * proceso=new Proceso((*listaBCP)[i]);

		// Obtiene una lista de los bloqueos asociados al proceso
		listaBloqueos=getBloqueos((*listaBCP)[i].idControl);

		// Si hay algun bloqueo asociado al proceso
		if (listaBloqueos->size()){

			// Agrega cada uno de los bloqueos asociados
			// Solo tomará en cuenta los primeros 20 bloqueos encontrados
			for (uint j = 0; j < listaBloqueos->size() && j <20; ++j) {

				// Agrega el bloqueo al proceso
				(*proceso)<<((*listaBloqueos)[j]);
			}
		}

		listaFinalDeProcesos->push_back(proceso);

	}
	return listaFinalDeProcesos;
}



//vector<Recurso> GestorDeConfiguracion::getRecursos() {
//}
//
//vector<Interaccion_Proceso_Recurso> GestorDeConfiguracion::getInteraccion_Procesos_Recursos() {
//}
//
//vector<Interaccion_Proceso_Proceso> GestorDeConfiguracion::getInteraccion_Procesos_Procesos() {
//}
//
vector<Bloqueo> *GestorDeConfiguracion::getBloqueos() {
	GestorDeFichero<Bloqueo> gestorBloqueos(NOMBRE_FICHERO_DE_BLOQUEOS);
	return gestorBloqueos.getLista();
}

vector<Bloqueo> *GestorDeConfiguracion::getBloqueos(int idControlDelProceso) {
	// Contiene todos los bloqueos del fichero
	vector<Bloqueo> *listaTotalBloqueos=getBloqueos();

	// Aqui se guardara la Lista de los bloqueos filtrados por el idControlDelProceso
	vector<Bloqueo> *listaDeBloqueosFiltrados=new vector<Bloqueo>();

	// Revisa todos los elementos de la lista y los agrega
	for (uint i = 0; i < listaTotalBloqueos->size(); ++i) {

		// Si el id del proceso en la lista total es igual al buscado
		if ((*listaTotalBloqueos)[i].getIDControlProceso() == idControlDelProceso){

			// Lo agrega a la lista de los filtrados
			listaDeBloqueosFiltrados->push_back(listaTotalBloqueos->operator [](i));
		}
	}

	return listaDeBloqueosFiltrados;
}

void GestorDeConfiguracion::addBloqueo(Bloqueo bloqueo) {
	GestorDeFichero<Bloqueo> gestorBloqueos(NOMBRE_FICHERO_DE_BLOQUEOS);
	gestorBloqueos.add(bloqueo);
}

uint GestorDeConfiguracion::getCantidadDeBloqueos() {
	GestorDeFichero<Bloqueo> gestorBloqueos(NOMBRE_FICHERO_DE_BLOQUEOS);
	return gestorBloqueos.getCantElem();
}

uint GestorDeConfiguracion::getCantidadDeProcesos() {
	GestorDeFichero<Proceso> gestorProcesos(NOMBRE_FICHERO_DE_PROCESOS);
	return gestorProcesos.getCantElem();
}

uint GestorDeConfiguracion::getCantidadDeRecursos() {
	GestorDeFichero<Recurso> gestorRecursos(NOMBRE_FICHERO_DE_RECURSOS);
	return gestorRecursos.getCantElem();
}
