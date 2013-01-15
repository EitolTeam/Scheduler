/*
 * Sennal.cpp
 *
 *  Created on: 11/11/2012
 *      Author: hector
 */

#include "Sennal.h"




void Sennal::addSignalHandler(int signal,
		void (*hdl)(int , siginfo_t*, void*)) {

	struct sigaction *act=new struct sigaction();

	/** Inicializa la zona de memoria **/
	memset (act, '\0', sizeof(struct sigaction));

	act->sa_sigaction = hdl;

	act->sa_flags = SA_SIGINFO;

	if (sigaction(signal, act, NULL) < 0) {
		perror ("sigaction ERROR CON LA SEÑAL");
		return;
	}
}

Sennal::~Sennal() {
	// TODO Auto-generated destructor stub
}

