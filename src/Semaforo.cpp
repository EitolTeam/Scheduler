/*
 * Semaforo.cpp
 *
 *  Created on: 03/07/2012
 *      Author: hector
 */

#include "Semaforo.h"
#include <stdio.h>
#include <ctime>

Semaforo::Semaforo(key_t key, int initValue) {
	srand(time(0));

	this->key= key;

	// Obtiene el semaforo
	this->id= semget (key, 1, 0777 | IPC_CREAT);

	if(id==-1){
		perror("Falla al crear el semaforo");
	}

	// Inicializa
	setValue(initValue);
}

void Semaforo::setValue(int value) {
	_unionSem.value=value;

	if(semctl(id,0,SETVAL,_unionSem)==-1){
		perror("Falla al inicializar el semáforo");
	}
}

void Semaforo::waitInQueue() {
	semOP(-1*(getNumberOfWaitingProcess()+1));
}

void Semaforo::signal(uint n) {
	semOP(n);
}

void Semaforo::wait(uint n) {
	semOP(-1*n);
}

void Semaforo::semOP(signed int op) {
	sembuf _op = { 0u, static_cast<short>(op) ,SEM_UNDO };
	semop (id, &_op, 1);
}

int Semaforo::getValue() {
	return _getSomeValue(GETVAL);
}

Semaforo::~Semaforo() {
	// Remueve el semaforo creado
	//semctl( id, 0, IPC_RMID); // TODO
}

int Semaforo::getNumberOfWaitingProcess() const {
	return _getSomeValue(GETNCNT);
}

int Semaforo::getZCount() const {
	return _getSomeValue(GETZCNT);
}

int Semaforo::_getSomeValue(int flag) const{
	int sem_value;
	if ((sem_value = semctl(id, 0, flag, 0)) == -1){
		perror("Error al obtener el valor del semaforo");
		return -1;
	}
	return sem_value;
}
