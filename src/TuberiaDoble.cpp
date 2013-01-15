/*
 * TuberiaDoble.cpp
 *
 *  Created on: 08/11/2012
 *      Author: hector
 */

#include "TuberiaDoble.h"

TuberiaDoble::TuberiaDoble()
{

}

TuberiaDoble::TuberiaDoble(Tuberia *tR, Tuberia *tW) {
	if (tR){
		this->t1=*tR;
		t1.setIOMode(r);
	}

	if (tW){

		this->t2=*tW;
		t2.setIOMode(w);
	}
}

int TuberiaDoble::setIOMode(IO_Mode ioT1, IO_Mode ioT2) {
	// Si los modos de los dos tubos son iguales
	if (ioT1==ioT2){
		return -1;
	}

	t1.setIOMode(ioT1);
	t2.setIOMode(ioT2);

	return 0;
}

int TuberiaDoble::read(char* container, size_t numberOfBytes) {
	if (getReadTuberia()==NULL){
		return -1;
	}
	return getReadTuberia()->read(container,numberOfBytes);
}

int TuberiaDoble::write(char* structure, size_t size) {
	if (getWriteTuberia()==NULL){
		return -1;
	}
	return getWriteTuberia()->write(structure,size);
}

Tuberia * TuberiaDoble::getReadTuberia() {
	return t1.getMode()==r? &t1 : (t2.getMode()==r?&t2 :NULL);
}

Tuberia* TuberiaDoble::getWriteTuberia() {
	return t1.getMode()==w? &t1 : (t2.getMode()==w?&t2 :NULL);
}



TuberiaDoble::~TuberiaDoble() {
	// TODO Auto-generated destructor stub
}

