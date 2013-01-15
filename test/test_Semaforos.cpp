/*
 * test_FileSize.cpp
 *
 *  Created on: 09/01/2013
 *      Author: hector
 *
 *      Prueba de la clase Semaforo.
 *
 *      Un hermano hace un signal y el otro un wait
 */
#include <iostream>
using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Semaforo.h"
#include <stdio.h>

int main(){

	Semaforo sem(0);

	pid_t pid=fork();

	if (!pid){
		while(true){
			sleep(2);
			printf("Hermano Menor: Signal \n");
			sem.signal();
		}
		exit(1);
	}else{
		pid=fork();
		if (!pid){
			while(true){
				sem.wait();
				printf("Hermano Mayor: Me desbloque'o \n");
			}
		}
	}
}
