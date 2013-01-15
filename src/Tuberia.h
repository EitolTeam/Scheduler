/*
 * Tuberia.h
 *
 *  Created on: 29/10/2012
 *      Author: hector
 */

#ifndef TUBERIA_H_
#define TUBERIA_H_

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/** Tamaño, en bytes, del buffer de lectura y escritura **/
#define SIZE_OF_BUFFER 100

/** Indica un modo de operación de e/s **/
enum IO_Mode{
	w=0,    // Escritura
	r,     	// Lectura
	OFF    	// Desactivada
};

/** Implementación orientada a objetos de una tubería posix **/
class Tuberia {
public:

	Tuberia();

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

	/** Asigna un modo de operación de entrada/salida
	 *
	 * @param mode Modo de operación a asignar
	 */
	void setIOMode(IO_Mode mode);

	/** Destructor
	 *
	 *  Cierra los descriptores
	 */
	virtual ~Tuberia();

	/** Retorna el modo la tuberia **/
	inline IO_Mode getMode() const {
		return _mode;
	}

private:

	/** Modo de e/s **/
	IO_Mode _mode;

	/** Descriptor de fichero que indican el final y el
	 *  inicio de la tubería. Donde:
	 *  · fd[0] es el descriptor de lectura
	 *  · fd[1] es el descriptor de escritura
	 */
	int fd[2];

	/** Buffer de lectura /escritura **/
	char buffer[SIZE_OF_BUFFER];

	/** Tamaño en bytes de la estructura standard de lectura
	 *  y escritura
	 */
	static size_t _sizeOfStandardStructure;
};

#endif /* TUBERIA_H_ */
