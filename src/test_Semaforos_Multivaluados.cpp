/*
 * test_FileSize.cpp
 *
 *  Created on: 09/01/2013
 *      Author: hector
 *
 *      Prueba de la clase Semaforo.
 *
 *      El hijo hace un signal y el padre lo libera
 */
#include <iostream>
using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Semaforo.h"
#include <stdio.h>

int main(){

	// Se inicializa el semaforo en 5
	Semaforo sem(5,0);

	// Piden 4 tickets
	{
		if (!fork()){
			printf("\n Soy un hijo 1 que hace un wait semvalue=%d \n",sem.getValue());
			sem.waitInQueue();
			printf("\n Soy un hijo 1 que despertó!!!!!!!!!!!!!!!!!!!!!\n");
			exit(1);
		}
		sleep(1);
		if (!fork()){
			printf("\n Soy un hijo 2 que hace un wait semvalue=%d \n",sem.getValue());
			sem.waitInQueue();
			printf("\n Soy un hijo 2 que despertó!!!!!!!!!!!!!1\n");
			exit(1);
		}
		sleep(1);
		if (!fork()){
			printf("\n Soy un hijo 3 que hace un wait semvalue=%d\n",sem.getValue());
			sem.waitInQueue();
			printf("\n Soy un hijo 3 que despertó\n!!!!!!!!!!1");
			exit(1);
		}
		sleep(1);
		if (!fork()){
			printf("\n Soy un hijo 4 que hace un wait semvalue=%d \n",sem.getValue());
			sem.waitInQueue();
			printf("\n Soy un hijo 4 que despertó\n!!!!!!!!!!1");
			exit(1);
		}
	}

	if (fork())	{
		int i=0;
		sleep(5);
		// Padre
		while(i++<5 ){
			printf("\nPADRE: Doy un ticket SIGNAL\n");
			printf("sem.getValue()==%d \n",sem.getValue());
			sem.signal();
			sleep(1);
		}
	}

}

