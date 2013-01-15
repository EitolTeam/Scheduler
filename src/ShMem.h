/*
 * ShMem.h
 *
 *  Created on: 03/07/2012
 *      Author: hector
 */

#ifndef SHMEM_H_
#define SHMEM_H_
#include <sys/shm.h>
#include <unistd.h>

ShMem<int> i;


/** Wrapper genérica que abstrae el concepto de memoria compartida **/
template<typename  T> class ShMem {
public:

	/** Constructor
	 *
	 * @param size Cantidad de elementos, contiguos y de tipo T,
	 * 			   que almacenará la memoria compartida
	 *
	 * @example Si size==4 and T==int and initValue==0 entonces
	 *          El buffer seria algo así
	 *          _______
	 *         |0|0|0|0|
	 * 		   ---------
	 */
	ShMem(int size);

	/** Retorna un elemento del buffer
	 * 
	 * @param idx Índice del elemento a acceder
	 * 
	 * @return El elemento buscado en caso de que idx esté dentro del
	 * 		   rango permitido, en caso contrario retorna una refencia
	 * 		   nula
	 * 		   
	 * @overload
	 */
	T& operator[](uint idx){

		if (idx>=sizeOfBuffer && idx<0u){
			perror("ShMem Memoria Fuera de rango");
			exit(1);
		}
		return buffer[idx];
	}

	/** Retorna un puntero constante al buffer **/
	inline const T* getBuffer() const {
		return const_cast<const T>(buffer);
	}

	/** Retorna el id de la shm **/
	inline int getIdMemoria() const {
		return idMemoria;
	}

	/** Retorna la clave de la shm **/
	inline key_t getKey() const {
		return key;
	}

	/** Retorna el tamaño del buffer **/
	inline uint getSizeOfBuffer() const {
		return sizeOfBuffer;
	}

	/** Inicializa la zona de memoria compartida con ceros (0)
	 *
	 *  @note Solo funciona con los tipos primitivos
	 */
	void inicializar(T initValue){
		// Inicializa el buffer
		for (uint i = 0u; i < sizeOfBuffer; buffer[i++]=initValue);
	}

	/** Imprime en pantalla la zona de memoria
	 *
	 *  @note Para depuracion
	 */
	void imprimir();

	virtual ~ShMem();
private:

	/** Clave para accesar a la shm **/
	key_t key;

	/** Id de la shm **/
	int idMemoria;

	/** Buffer donde se almacenar'a la shm **/
	T *buffer;

	/** Tamaño del buffer **/
	uint sizeOfBuffer;
};

/** Los templates se deben definir en un fichero */
template<typename T>
ShMem<T>::ShMem(int size) : sizeOfBuffer(size) {

	srand(time(0));

	// Genera la clave con un n'umero aleatorio
	key=ftok ("/bin/ls", rand()%999+((srand(time(0)),rand()+10)%10));

	// Reserva la zona de memoria
	idMemoria=shmget (key, sizeof(T)*size, 0777 | IPC_CREAT);

	buffer=(T *)shmat (idMemoria, (char *)0, 0);


}

template<typename T> void ShMem<T>::imprimir(){

	for (uint i = 0; i < sizeOfBuffer; printf("[%d]",buffer[i++]));
	printf("\n");
}

template<typename T> ShMem<T>::~ShMem(){  // TODO
	// shmdt ((char *)Memoria);
	// shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
}


#endif /* SHMEM_H_ */
