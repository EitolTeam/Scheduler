/*
 * Tuberia.cpp
 *
 *  Created on: 29/10/2012
 *      Author: hector
 */

#include "Tuberia.h"
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ	0
#define WRITE 	1

size_t Tuberia::_sizeOfStandardStructure=0;

Tuberia::Tuberia():
		_mode(OFF) {
	// Crea los descriptores
	pipe(fd);
}

int Tuberia::read(char * container, size_t numberOfBytes) {

	// Si la tubería está cerrada o está en modo escritura
	if (_mode==OFF || _mode==w ||
			!(numberOfBytes || _sizeOfStandardStructure)){
		perror("La tubería no está abierta para lectura");
		return -1;
	}

	// Lee de la tubería
	::read (fd[READ], container, numberOfBytes);

	return 1;
}

int Tuberia::write(char * structure,size_t numberOfBytes) {
	if (_mode==OFF || _mode==r ||
			!(numberOfBytes || _sizeOfStandardStructure)){
		perror("La tubería no está abierta para escritura");
		return -1;
	}

	::write (fd[WRITE], structure, numberOfBytes);

	return 1;
}

void Tuberia::setIOMode(IO_Mode mode) {
	this->_mode=mode;
	close( _mode==r ? fd[WRITE] : fd[READ] );
}

Tuberia::~Tuberia() {
	// Cierra los descriptores
	//close( _mode==w ? fd[WRITE] : fd[READ] );
}

