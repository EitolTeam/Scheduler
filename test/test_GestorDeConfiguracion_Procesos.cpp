/*
 ============================================================================
 Author      : Hector
 Description : Prueba de la clase gestor de configuracion.
 	 	 	   Crea procesos a partir de los ficheros

 ============================================================================
 */


#include <gtkmm/main.h>
#include "GestorDeConfiguracion.h"
#include "Proceso.h"


int main (int argc, char *argv[])
{
	vector<Proceso*> *listaDeProcesos=GestorDeConfiguracion::getProcesos();

	if ( listaDeProcesos==NULL ){
		return 1;
	}

	printf("Lista Size=%u",listaDeProcesos->size());

	for (uint i = 0; i < listaDeProcesos->size(); ++i) {
		printf("Proceso PID = %d \n",(*listaDeProcesos)[i]->getPID());
		Proceso p=*(*listaDeProcesos)[i];
		printf("Proceso Bloqueo PID = %d \n",(*listaDeProcesos)[i]->getBCP().bloqueos[0].getIDControlProceso());
	}
}

//// read a file into memory
//#include <iostream>
//#include <fstream>
//using namespace std;
//
//int main () {
//	int length;
//	char * buffer;
//
//	ifstream is;
//	is.open ("Procesos.cfg", ios::binary );
//
//	// get length of file:
//	is.seekg (0, ios::end);
//	length = is.tellg();
//	is.seekg (0, ios::beg);
//
//
//	string nombre("Procesos.cfg");
//	is.close();
//	is.open (nombre.c_str(), ios::binary );
//
//
//	// get length of file:
//	is.seekg (0, ios::end);
//	length = is.tellg();
//	is.seekg (0, ios::beg);
//
//	is.close();
//
//	//printf("%s %d",buffer,length);
//
//	return 0;
//}
