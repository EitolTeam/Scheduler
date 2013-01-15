/*
 * Interaccion.h
 *
 *  Created on: 14/12/2012
 *      Author: hector
 */

#ifndef INTERACCIONES_H_
#define INTERACCIONES_H_


/** Modela una interacción entre un proceso y un recurso **/
class Interaccion_Proceso_Recurso {
public:

	/** Constructor
	 *
	 * @param idControl ID de control del proceso
	 * @param idRecurso ID de control de recurso
	 * @param numeroDeInstanciasNecesarias TODO
	 */
	Interaccion_Proceso_Recurso(int idControl,
			int idRecurso,
			int numeroDeInstanciasNecesarias):
				idControl(idControl),
				idRecurso(idRecurso),
				numeroDeInstanciasNecesarias(numeroDeInstanciasNecesarias)
{}

	/** ID de control del proceso **/
	int idControl;

	/** ID de control del recurso**/
	int idRecurso;

	/** TODO: POR DEFINIR **/
	int numeroDeInstanciasNecesarias;

};

/** Tipo de interacción entre procesos **/
enum TIPO_DE_INTERACCION_PROCESO_PROCESO{

	/** No tienen conocimiento de la existencia de otros procesos.
	 *  Son independientes. Los procesos compiten por los recursos **/
	INDEPENDIENTES=0,

	/** Tienen conocimiento indirecto de la existencia de otros procesos.
	 *  Los procesos comparten un recurso común. Los procesos se coordinan
	 *  para usar ese recurso común mediante sincronización. **/
	RECURSO_COMUN=1,

	/** Tienen conocimiento directo de la existencia de otros procesos.
	 * Los procesos trabajan en un fin común y se comunican entre sí. **/
	COOPERANTES=2
};

/** Modela una interacción entre procesos **/
class Interaccion_Proceso_Proceso {
public:

	/** Constructor
	 *
	 * @param idControlProcess1 ID de control del proceso 1
	 * @param idControlProcess2 ID de control del proceso 2
	 * @param tipoDeInteraccion Tipo de interacción entre los procesos
	 */
	Interaccion_Proceso_Proceso(int idControlProcess1,
			int idControlProcess2,
			TIPO_DE_INTERACCION_PROCESO_PROCESO tipoDeInteraccion):
				idControlProcess1(idControlProcess1),
				idControlProcess2(idControlProcess2),
				tipoDeInteraccion(tipoDeInteraccion){}

	/** ID de control del proceso 1 **/
	int idControlProcess1;

	/** ID de control del proceso 2 **/
	int idControlProcess2;

	/** Tipo de interacción entre los procesos **/
	TIPO_DE_INTERACCION_PROCESO_PROCESO tipoDeInteraccion;
};

#endif /* INTERACCIONES_H_ */
