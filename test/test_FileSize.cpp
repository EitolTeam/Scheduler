/*
 * test_FileSize.cpp
 *
 *  Created on: 09/01/2013
 *      Author: hector
 */
#include <iostream>
using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



// TODO: No se que pasa con la implementacion en el gestor de ficheros
//       que da error en la funcion getFileSize.
//       Por razones de tiempo me veo obligado a usar las librerias boost para resolver el problema
//
int fileSize(const char* fichero )
{
	struct stat filestatus;
	stat( fichero, &filestatus );
	cout << filestatus.st_size << " bytes\n";
	return filestatus.st_size;
}

int main(){

	fileSize("Procesos.cfg");
}
