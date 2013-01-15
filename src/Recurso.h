/*
 * Recurso.h
 *
 *  Created on: 14/12/2012
 *      Author: hector
 */

#ifndef RECURSO_H_
#define RECURSO_H_
#include <string.h>



/** Permite clasificar un recurso según su tipo de compartición **/
enum TIPO_DE_COMPARTICION_DE_RECURSO{
	NO_COMPARTIBLE=0,
	COMPARTIBLE
};

/** Clasifica los recursos según su perdurancia **/
enum PERDURANCIA_DEL_RECURSO{
	REUTILIZABLE=0,
	CONSUMIBLE,
};

/** Modela un recurso del sistema
 * **/
class Recurso: public Proceso {
public:

	/** Constructor
	 *
	 * @param idRecurso ID del recurso.
	 * @param nombre Nombre del recurso.
	 * @param tipo Indica si el recurso es compartible.
	 * @param perdurancia Indica si el recurso es consumible.
	 * @param numeroDeInstancias TODO
	 * @param esCrtitico Indica si un recurso es crítico.
	 */
	Recurso(int idRecurso,
			char nombre[200],
			TIPO_DE_COMPARTICION_DE_RECURSO tipo,
			PERDURANCIA_DEL_RECURSO perdurancia,
			int numeroDeInstancias,
			bool esCrtitico,
			Bloqueo bloqueo):
				idRecurso(idRecurso),
				tipo(tipo),
				perdurancia(perdurancia),
				numeroDeInstancias(numeroDeInstancias),
				esCrtitico(esCrtitico),
				bloqueo(bloqueo){
		strcpy(this->nombre,nombre);
	}

private:

	/** ID del recurso **/
	int idRecurso;

	/** Nombre del recurso **/
	char nombre[200];

	/** Indica si el recurso es compartible **/
	TIPO_DE_COMPARTICION_DE_RECURSO tipo;

	/** Indica si el recurso es consumible **/
	PERDURANCIA_DEL_RECURSO perdurancia;

	/** TODO **/
	int numeroDeInstancias;

	/** Indica si un recurso es crítico  **/
	bool esCrtitico;

	/** Bloqueo que ocurre cuando se accede al recurso **/
	Bloqueo bloqueo;
};


#endif /* RECURSO_H_ */
