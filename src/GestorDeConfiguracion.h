/*
 * GestorDeConfiguracion.h
 *
 *  Created on: 14/12/2012
 *      Author: hector
 */

#ifndef GESTORDECONFIGURACION_H_
#define GESTORDECONFIGURACION_H_

#include <vector>
#include "Proceso.h"
#include "Recurso.h"
#include "Interacciones.h"

using std::vector;

#define NOMBRE_FICHERO_DE_PROCESOS "Procesos.conf"
#define NOMBRE_FICHERO_DE_RECURSOS "Recursos.conf"
#define NOMBRE_FICHERO_DE_BLOQUEOS "Bloqueos.conf"
#define NOMBRE_FICHERO_DE_INTERACION_PROCESOS_PROCESOS "Interacion Procesos-Procesos.conf"
#define NOMBRE_FICHERO_DE_INTERACION_PROCESOS_RECURSOS "Interacion Procesos-Recursos.conf"


/** Clase encargada de levantar la informacion desde los ficheros **/
class GestorDeConfiguracion {
public:
	GestorDeConfiguracion();

	/** Retorna un vector de procesos a partir del fichero de configuración de procesos
	 *
	 *  Los procesos pueden ser definidos, dentro del fichero, de la siguiente forma:
	 *
	 *  IDControl: entero
	 *  ID : entero.
	 *  PID : entero
	 *  Grado de prioridad: entero.
	 *  Consumo acumulado de CPU. Entero.
	 *  Ráfagas de ejecución: Array de enteros [20 posiciones]
	 *  Tiempos de bloqueo: Array de la estructura de bloqueos [20 posiciones]
	 *  Instante de llegada - Entero
	 *  Tipo de proceso – Entero – 0: Batch || 1: Tiempo real || 2:Interactivos
	 *
	 *  @note se retorna un puntero para evitar la doble instanciacion de los procesos
	 */
	static vector<Proceso*> * getProcesos();

	/** Retorna un vector de recursos a partir del fichero de configuración de recursos
	 *
	 *  La estructura de lectura de los recursos es la siguiente:
	 *
	 *  ID recurso – entero único que especifica el reconocimiento del recurso en la simulación.
	 *  Nombre recurso – string[200]
	 *  Tipo de recurso. - Entero (0 .- no compartible || 1.- compartible)
	 *  Tipo de recurso2 – Entero (0.- reutilizable || 1.- consumible)
	 *  Número de instancias. – Entero
	 *  Flag recurso critico – Entero (0.- NO es || 1.- Si es)
	 */
	static vector<Recurso> * getRecursos();

	/** Retorna un vector de Interaccion_Procesos_Recursos a partir del fichero de
	 * configuración de Interaccion_Procesos_Recursos
	 *
	 *  La estructura del fichero es la siguiente:
	 *  IDControl.
	 *  ID recurso.
	 *  Número de instancias necesarias. – Entero
	 */
	static vector<Interaccion_Proceso_Recurso> *getInteraccion_Procesos_Recursos();

	/** Retorna un vector de Interaccion_Procesos_Procesos a partir del fichero de
	 * configuración de Interaccion_Procesos_Procesos
	 *
	 *  La estructura del fichero es la siguiente:
	 *
	 *  IDControl process1 – Entero.
	 *  IDControl process2 – Entero.
	 *  Tipo de interacción. (1-2-3 explicadas previamente)
	 */
	static vector<Interaccion_Proceso_Proceso> *getInteraccion_Procesos_Procesos();

	/** Retorna un vector de bloqueos a partir del fichero de configuración de bloqueos
	 *
	 *  La estructura del fichero es la siguiente:
	 *
	 *  IDControl
	 *  Tiempo de bloqueo
	 *  ID recurso.
	 */
	static vector<Bloqueo> *getBloqueos();

	/** Retorna un vector de bloqueos asociados a un identificador de proceso
	 *  a partir del fichero de configuración de bloqueos
	 *
	 *  @param idControlDelProceso ID de control del proceso objetivo.
	 *
	 *  La estructura del fichero es la siguiente:
	 *
	 *  IDControl
	 *  Tiempo de bloqueo
	 *  ID recurso.
	 */
	static vector<Bloqueo> *getBloqueos(int idControlDelProceso);

	/** Agrega un bloqueo al fichero de bloqueos
	 *
	 * @param bloqueo Bloqueo a agregar
	 */
	static void addBloqueo(Bloqueo bloqueo);

	/** Retorna la cantidad de bloqueos almacenados en el fichero de bloqueos **/
	static uint getCantidadDeBloqueos();

	/** Retorna la cantidad de procesos almacenados en el fichero de bloqueos **/
	static uint getCantidadDeProcesos();

	/** Retorna la cantidad de recursos almacenados en el fichero de bloqueos **/
	static uint getCantidadDeRecursos();

private:

};

#endif /* GESTORDECONFIGURACION_H_ */
