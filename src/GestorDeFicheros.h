/*
 * ModeloGestorDeFichero.h
 *
 *  Created on: 24/04/2012
 *      Author: hector
 */

#ifndef MODELOGESTORDEFICHERO_H_
#define MODELOGESTORDEFICHERO_H_

#include <iostream>
#include <list>
#include <fstream> // Manejo de ficheros

#include <iosfwd>
#include <errno.h>
#include <string.h>
#include <glib-2.0/glib/gstdio.h>

using namespace std;


/** Permite rescatar elementos de un fichero binario
 *
 *  @param Tipo Tipo de objeto que almacenará el fichero
 */
template<class Tipo> class GestorDeFichero {

public:

	/** Constructor
	 *  @param nombreDelFichero Nombre del fichero a operar
	 */
	GestorDeFichero(string nombreDelFichero);

	/** Retorna una lista que contiene todos los objetos del fichero
	 *
	 *  @return Un puntero a una lista en donde se ubican todos los
	 *  		objetos descerializados que estaban almacenados en el
	 *  		fichero. En caso de que el fichero esté vacío entonces
	 *  		retorna una lista vacía.
	 *  		En caso de que el fichero no exista retorna NULL;
	 */
	vector<Tipo>* getLista();

	/** Retorna el objeto ubicado en la posición @a pos del fichero
	 *
	 *  @param pos Posición del objeto a retornar
	 *  @return El objeto ubicado en la posición @a pos del fichero
	 */
	Tipo get(uint pos);

	/** Agrega un objeto al fichero
	 *
	 *  @param obj Objeto a agregar
	 */
	void add(Tipo obj);

	/** Agrega un objeto al fichero (Análogo al método add)
	 *
	 * @param obj Objeto a agregar
	 * @return El mismo objeto luego de operar
	 */
	GestorDeFichero<Tipo>& operator << (Tipo obj){
		return add(obj) , this;
	}

	/** Retorna la cantidad de objetos en el fichero
	 *
	 *  @return La cantidad de objetos en el fichero.
	 *          Si ocurre algun problema al momento de leer el fichero retorna -1.
	 */
	int getCantElem();

	/** Indica si el fichero está vacío
	 *
	 *  @return true en caso de que esté vacío. False en caso contrario
	 */
	bool isEmpty();

	/** Retorna el nombre del fichero en donde se almacenan y recolectan los objetos
	 *
	 *  @return El nombre del fichero
	 */
	string getnombreDelFichero();

	/** Asigna el nombre del fichero en donde se almacenan y recolectan los objetos
	 *
	 *  @param El nombre del fichero
	 */
	void setnombreDelFichero(string nombreDelFichero);

protected:

	/** Agrega un objeto al fichero de forma más eficiente que add(Tipo)
	 *
	 *  @param obj Objeto a agregar
	 *
	 *  @note Antes de usarlo el fichero debe estar abierto en modo escritura
	 *  	  puesto que ese método no abre ni cierra el fichero
	 */
	void _addFast(Tipo obj);

	/** Rescata un objeto del fichero de forma más eficiente que get(Tipo)
	 *
	 *  @param pos Posición del objeto a rescatar
	 *
	 *  @note Antes de usarlo el fichero debe estar abierto en modo lectura
	 *  	  puesto que ese método no abre ni cierra el fichero.
	 */
	Tipo _getFast(uint pos);

	/** Nombre del fichero */
	string nombreDelFichero;

	/** Fichero en el cual se harán las operaciones */
	fstream _fichero;
};


template<class Tipo>
inline GestorDeFichero<Tipo>::GestorDeFichero(string nombreDelFichero) {
	this->nombreDelFichero=nombreDelFichero;
}

template<class Tipo>
inline string GestorDeFichero<Tipo>::getnombreDelFichero() {
	return nombreDelFichero;
}

template<class Tipo>
inline vector<Tipo>* GestorDeFichero<Tipo>::getLista() {

	vector<Tipo> *r=new vector<Tipo>(); // Para retornar

	int cantEle=getCantElem();

	// Si no se pudo leer el fichero retorna null
	if (cantEle==0){
		return NULL;
	}

	// Abre el fichero para escritura, agregar en modo binario
	_fichero.open(nombreDelFichero.c_str(),ios::in | ios::binary);

	int i=0;

	// Agrega a la lista de retorno todos los elementos del fichero
	while (i<cantEle){
		r->push_back(_getFast(i++));
	}

	// Cierra el fichero
	_fichero.close();

	return r;
}

template<class Tipo>
inline Tipo GestorDeFichero<Tipo>::get(uint pos) {

	// Abre el fichero para escritura en modo binario
	_fichero.open(nombreDelFichero.c_str(),ios::in | ios::binary);

	// Si la cantidad de elementos en el archivo es menor que pos
	if ( getCantElem() < pos ){
		_fichero.close();

		// retorna un elemento vacío
		return Tipo();
	}

	// Se ubica en la posición del elemento en el fichero
	_fichero.seekg(pos*sizeof(Tipo),ios::beg);

	// Para rescatar el elemento
	Tipo elem;

	// Escribe en el elemento desde el fichero
	_fichero.read(reinterpret_cast<char *>(&elem), sizeof(Tipo));

	// Cierra el fichero
	_fichero.close();

	// Retorna el elemento leido
	return elem;
}

template<class Tipo>
inline void GestorDeFichero<Tipo>::add(Tipo obj) {
	// Abre el fichero para escritura, agregar y en modo binario
	_fichero.open(nombreDelFichero.c_str(),ios::out | ios::app | ios::binary);

	// Escribe el objeto en el fichero
	_fichero.write(reinterpret_cast<char *>(&obj), sizeof(Tipo));

	// Cierra el fichero
	_fichero.close();
}

template<class Tipo>
inline int GestorDeFichero<Tipo>::getCantElem() {

	//
	//		bool flag=false;
	//
	//		// Si el fichero no esta abierto
	//		if (!_fichero.is_open()){
	//
	//			// Entonces lo abre
	//			_fichero.open(nombreDelFichero.c_str(),ios::binary);
	//
	//			flag=true;
	//		}
	//
	//		// Se ubica en el final del fichero
	//		_fichero.seekg(0,ios::end);
	//
	//		int telg_=_fichero.tellg();
	//
	//		printf("asd %d",telg_);
	//
	//		// Divide la cantidad de bytes que hay entre el tamaño en bites
	//		// del tipo elemento a buscar
	//		uint size=static_cast<uint>(_fichero.tellg()/sizeof(Tipo));
	//
	//		if (flag){
	//			_fichero.close();
	//		}
	//		return size;

	// TODO: Determinar las causas de las fallas del código anterior
	//

	struct stat st;

	// Si no se pudo obtener la estádistica del fichero
	if (stat(nombreDelFichero.c_str(), &st)){
		fprintf(stderr, "No se puede determinar el size of %s: %s\n",
					nombreDelFichero.c_str(), strerror(errno));
		return -1;
	}

	// En caso contrario entonces la cantidad de elementos será:
	// el tamaño en bytes del fichero menos el tamaño en bytes del tipo elemento
	return st.st_size / sizeof(Tipo);
}

template<class Tipo>
inline bool GestorDeFichero<Tipo>::isEmpty() {
	return getCantElem()==0u;
}

template<class Tipo>
inline void GestorDeFichero<Tipo>::setnombreDelFichero(
		string nombreDelFichero) {
	GestorDeFichero::nombreDelFichero = nombreDelFichero;
}

template<class Tipo>
inline void GestorDeFichero<Tipo>::_addFast(Tipo obj) {

	// Escribe el objeto en el fichero
	_fichero.write(reinterpret_cast<char *>(&obj), sizeof(Tipo));
}


template<class Tipo>
inline Tipo GestorDeFichero<Tipo>::_getFast(uint pos) {

	// Se ubica en la posición @a pos en el fichero
	_fichero.seekg(pos * sizeof(Tipo), ios::beg);

	// Crea el elemento para cargar el objeto
	static Tipo ele;

	// Escribe en el elemento desde el fichero
	_fichero.read(reinterpret_cast<char*>(&ele), sizeof(Tipo));

	// Retorna un elemento construido a partir del elemento leído
	return ele;
}

#endif /* MODELOGESTORDEFICHERO_H_ */
