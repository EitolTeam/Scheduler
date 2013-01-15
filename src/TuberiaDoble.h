/*
 * TuberiaDoble.h
 *
 *  Created on: 08/11/2012
 *      Author: hector
 */

#ifndef TUBERIADOBLE_H_
#define TUBERIADOBLE_H_

#include <stdlib.h>
#include "Tuberia.h"

class TuberiaDoble {
public:

	TuberiaDoble();

	/** Construye la tubería doble a partir de dos tuberías
	 *
	 * @param tR Tubería de lectura
	 * @param tW Tubería de escritura
	 */
	TuberiaDoble(Tuberia *tR,Tuberia *tW);

	/** Asigna el modo de ambos tubos de la tubería
	 *
	 * @param ioT1 Modo del tubo #1
	 * @param ioT2 Modo del tubo #2
	 * @return 0 Si la operación se efectuó correctamente. -1 en caso contrario
	 */
	int setIOMode(IO_Mode ioT1,IO_Mode ioT2);

	/** Lee datos desde la tubería y los almacena el el buffer interno
	 *
	 *  @param container Donde se guardará la lectura
	 *  @param numberOfBytes Numero de bytes a leer
	 *  @return -1 en caso de error, En caso contrario retorna el número
	 *          de caracteres que fueron leídos.
	 */
	int read(char * container,size_t numberOfBytes=_sizeOfStandardStructure);

	/** Escribe en la tubería
	 *
	 * @param structure Puntero a la estructura a escribir
	 * @param size Tamaño en bytes de la estructura
	 * @return -1 en caso de error. 1 En caso de éxito.
	 */
	int write(char * structure,size_t size=_sizeOfStandardStructure);

	/** Asigna el tamaño en bytes de la estructura standard de lectura
	 *  y escritura
	 * @param size Tamaño a asignar
	 */
	inline void setSizeOfStandardStruct(size_t size){
		_sizeOfStandardStructure=size;
	}

	/** Retorna un puntero a la tubería de lectura
	 *
	 *  @return Un puntero a la tubería de lectura. NULL en caso
	 *          de que no exista ninguna
	 */
	Tuberia * getReadTuberia();

	/** Retorna un puntero a la tubería de escritura **/
	Tuberia * getWriteTuberia();

	virtual ~TuberiaDoble();

private:

	Tuberia t1;
	Tuberia t2;

	/** Tamaño en bytes de la estructura standard de lectura
	 *  y escritura
	 */
	static size_t _sizeOfStandardStructure;
};

#endif /* TUBERIADOBLE_H_ */
