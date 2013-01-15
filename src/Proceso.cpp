/*
 * Proceso.cpp
 *
 *  Created on: 31/03/2012
 *      Author: hector
 */

// Señal para que el proceso actual ejecute el método run()

#include "Proceso.h"
#include <error.h>
#include <err.h>


Proceso::Proceso(){
	// Inicializa su bcp con todo en 0
	_inicializar(BCP());
}

Proceso::Proceso(BCP bcp) {
	_inicializar(bcp);
}

void Proceso::_inicializar(BCP bcp) {
	bcp.idControl=bcp.pid;
	this->bcp=bcp;
	state=Paused;
	signal(SIG_FIN,&hijoFinalizado);
	signal(SIG_HIJO_LISTO,&despertador);
}


Proceso::ProcessError Proceso::start(){

	orig_mask=bloquearSennal(SIG_HIJO_LISTO);

	// Si el proceso ya estaba corriendo
	if (state == Running){
		return (activarSennal(),AlreadyStarted);
	}
	// Bifurca
	bcp.pid=fork();

	// El proceso actual ahora es el proceso hijo
	Proceso::_procesoActual=this;

	/********* Punto crítico ********/

	// Si es el proceso hijo
	if (!bcp.pid){

		this->bcp.pid=getpid();

		// Le manda un mensaje al padre indicándole que está listo
		kill(getppid(),SIG_HIJO_LISTO);

		// Asocia la señal SIG_RUN al método despertador
		signal(SIG_RUN,despertador);

		state=Running;

		activarSennal();

		// Lugar de la acción

		run();

		state=Finished;

		// Avisa al padre que el proceso concluyó
		kill(getppid(),SIG_FIN);

		// Termina el proceso hijo
		exit(1);

	}else{ // En caso de que sea el proceso padre

		signal(SIG_FIN,&hijoFinalizado);
		signal(SIG_HIJO_LISTO,&despertador);

		// desbloquea la señal de listo
		activarSennal();

		// Espera a que el hijo le envie una señal de listo
		pause();

	}

	// finaliza el método start en el padre
	return NoError;
}


void Proceso::hijoFinalizado(int int1) {
	printf("PID=%d Dice El hijo finalizó\n",getpid());
}

void Proceso::addBloqueo(Bloqueo bloqueo) {
	uint i=0;

	// Se ubica en el último elemento del vector de bloqueos
	// Nota: el último elemento es aquel el cual su campo
	// idControlProceso es igual a 0 (cero)
	for ( ; i<20 && bcp.bloqueos[i].getIDControlProceso(); ++i );

	// Si el vector de bloqueos estaba full
	if (i>=20){
		warn("El vector de Bloqueos del Proceso.pid==%d llego al límite",
				bloqueo.getIDControlProceso());
	}

	// En caso de que se pueda agregar
	else{
		bcp.bloqueos[i]=bloqueo;
	}

}

Proceso& Proceso::operator <<(Bloqueo bloqueo) {
	addBloqueo(bloqueo);
	return *this;
}

void Proceso::remoteHandler(int) {

	Proceso::_procesoActual->activarSennal();
}

void Proceso::despertador(int) {
	// Despierta el proceso
}

sigset_t Proceso::bloquearSennal(int signal) {

	// nueva mascara
	sigset_t newMask;

	sigset_t orig_mask;

	sigaddset (&newMask, signal);

	sigprocmask(SIG_BLOCK,&newMask,&orig_mask);

	return orig_mask;
}

void Proceso::activarSennal() {

	sigprocmask(SIG_SETMASK,&orig_mask,NULL);
}

Proceso *Proceso::_procesoActual=NULL;

sigset_t Proceso::orig_mask;
