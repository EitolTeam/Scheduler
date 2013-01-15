/*
 * Semaforo.h
 *
 *  Created on: 03/07/2012
 *      Author: hector
 */

#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/stat.h>

/** Implementacion orientada a objetos de un semaforo IPC (multivaluado).
 *
 */
class Semaforo {
public:

	/** Constructor
	 *
	 * @param initValue Valor inicial del semaforo
	 *
	 * @details El semaforo estará en "verde" por defecto
	 */
	Semaforo(key_t key,int initValue=1);

	/** Asigna un valor al semaforo
	 *
	 * @param value Valor a asignar
	 */
	void setValue(int value);

	/** Adquiere un recurso y espera en la cola su turno
	 */
	void waitInQueue();

	/** Adquiere un recurso y espera en la cola su turno
	 *
	 * @param n Cantidad de recursos a adquirir
	 */
	void wait(uint n=1);

	/** Libera @a n recursos
	 *
	 * @param n Cantidad de recursos a liberar
	 */
	void signal(uint n = 1);

	/** Retorna el valor del semaforo
	 *
	 *  @details Este valor indica la cantidad de procesos en cola
	 */
	int getValue();

	virtual ~Semaforo();

	/** Indica un tipo de operación sobre el semaforo **/
	enum OP{ SIMPLE_WAIT  =-1,   // Wait corriente
		WAIT_FOR_ZERO=	0,   // Espera por cero
		SIMPLE_SIGNAL=	1};  // Señal simple

	/** Realiza una operacion sobre el semáforo
	 *
	 *  @param op Operacion a realizar
	 */
	void semOP(signed int);

	/** Retorna el número de procesos en la cola de espera **/
	int getNumberOfWaitingProcess() const;

	/** Retorna el número de procesos que esperan a que el valor del semaforo
	 *  sea igual a cero
	 */
	int getZCount() const;

private:

	/** Retorna algun valor del semaforo (wrapper para semctl)
	 *
	 * @param flag Comando de `semctl' que indica el valor a obtener
	 */
	int _getSomeValue(int flag) const;

	/** Clave del semaforo **/
	key_t key;

	/** Id del semaforo **/
	int id;

	/** Para poder definir el semáforo **/
	union semun
	{
		int              value;
		struct semid_ds *buf;
		unsigned short  *array;
		struct seminfo  *__buf;
	} _unionSem;
};

#endif /* SEMAFORO_H_ */
