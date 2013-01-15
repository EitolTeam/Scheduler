/*
 * Sennal.h
 *
 *  Created on: 08/11/2012
 *      Author: hector
 */

#ifndef SENNAL_H_
#define SENNAL_H_

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Sennal {
public:

	/** Agrega un manejador para una señal
	 *
	 * @param signal Señal a asociar
	 * @param hdl Manejador asociado
	 */
	static void addSignalHandler(int signal,void (*hdl)(int sig,
										siginfo_t *siginfo,
											 void *context));

	virtual ~Sennal();

private:




};

#endif /* SENNAL_H_ */
