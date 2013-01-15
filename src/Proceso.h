/*
 * Proceso.h
 *
 *  Created on: 31/03/2012
 *      Author: hector
 */

#ifndef PROCESO_H_
#define PROCESO_H_

#include <unistd.h>
#include <glib-2.0/glib/gstdio.h> // Para g_print
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>



#define SIG_RUN SIGCONT         // Continuar la ejecución 		(Padre/Hijo)
#define SIG_FIN SIGCHLD 		// Fin de la rutina       		(Hijo/Padre)
#define SIG_HIJO_LISTO SIGCONT  // Proceso hijo creado y listo  (Hijo/Padre)


#define PATH_KEY 	"/bin/ls"	// Path del key IPC
#define NUM_KEY	 	33			// Número del key IPC
#define DEBUG_MODE 	true        // Indica si el programa est'a en modo debug

/** Modela un bloqueo de recurso **/
class Bloqueo{
public:

	/** Constructor
	 *
	 * @param idControlProceso ID del bloqueo
	 * @param tiempoDeBloqueo Tiempo de bloqueo
	 * @param idRecurso ID del recurso bloqueado
	 */
	Bloqueo(int idControlProceso=0, uint tiempoDeBloqueo=0, int idRecurso=0){
		this->idControlProceso=idControlProceso;
		this->tiempoDeBloqueo=tiempoDeBloqueo;
		this->idRecurso=idRecurso;
	}

	/** Retorna el id del bloqueo **/
	inline int getIdRecurso() const {
		return idRecurso;
	}

	/** Asigna el id del bloqueo
	 *
	 * @param idRecurso Id del recurso bloqueado
	 */
	inline void setIdRecurso(int idRecurso) {
		this->idRecurso = idRecurso;
	}

	/** Retorna el tiempo de bloqueo **/
	inline uint getTiempoDeBloqueo() const {
		return tiempoDeBloqueo;
	}

	/** Asigna el tiempo de bloqueo
	 *
	 * @param tiempoDeBloqueo Tiempo de bloqueo a asignar
	 */
	inline void setTiempoDeBloqueo(uint tiempoDeBloqueo) {
		this->tiempoDeBloqueo = tiempoDeBloqueo;
	}

	/** Retorna el id del proceso a bloquear **/
	inline int getIDControlProceso() const {
		return idControlProceso;
	}

	/** Asigna el id del bloqueo
	 *
	 * @param idControlProceso Id a asignar
	 */
	inline void setIDControlProceso(int idControlProceso) {
		this->idControlProceso = idControlProceso;
	}

private:

	/** ID del proceso a bloquear **/
	int idControlProceso;

	/** Tiempod de bloqueo **/
	uint tiempoDeBloqueo;

	/** ID del recurso bloqueado **/
	int idRecurso;
};

/** Clase abstracta que permite crear procesos.
 *
 * 	Para poder usar esta clase usted debe heredar de ella e implementar
 * 	el método run() en la clase heredada.
 * 	Dicho método run() contendrá la rutina de ejecución del proceso.
 * 	Para arrancar el proceso bastará con instanciar un objeto de la clase
 * 	heredada y luego ejecutar una llamada al método start().
 *
 * 	@note Clase reutilizable
 * 	@author Hector Oliveros
 */
class Proceso {

public:

	/** Bloque de control de proceso (Process Control Block)
	 */
	struct BCP{
		BCP(){
			idControl=pid=ppid=gradoDePrioridad=
					consumoAcumuladoDeCPU=instanteDeLlegada=0;
			tipoDeProceso=BATCH;

			memset(reinterpret_cast<void*>(rafagasDeEjecucion),0,
					sizeof(rafagasDeEjecucion));
		}

		/** ID de control de proceso (ID del sistema) **/
		int idControl;

		/** PID del proceso
		  *  @note Valdrá  0 cuando el proceso no haya arrancado **/
		int pid;

		/** PPID (PID del padre) **/
		pid_t ppid;

		/** Grado de prioridad **/
		int gradoDePrioridad;

		/** Consumo acumulado de CPU **/
		int consumoAcumuladoDeCPU;

		/** Rafagas de ejecución de CPU **/
		int rafagasDeEjecucion[20];

		/** Tiempos de Bloqueo **/
		Bloqueo bloqueos[20];

		/** Instante de llegada **/
		int instanteDeLlegada;

		/** Tipo de proceso **/
		enum TipoDeProceso{
			BATCH	     = 0,
			TIEMPO_REAL  = 1,
			INTERACTIVOS = 2
		} tipoDeProceso;

	};

	Proceso();

	Proceso(BCP bcp);

	virtual ~Proceso(){}

	/** Describe los estados del proceso */
	enum ProcessState {
		Finished, // Finalizado
		Running,  // Corriendo
		Paused
	};
	// Pausado
	/** Errores que se pueden producir al crear el proceso */
	enum ProcessError {
		NoError = 0,    // Sin error
		FailedToStart,  // Falla al iniciar
		AlreadyStarted, // Ya estaba iniciado
		UnknownError    // Error desconocido
	};
	// Error desconocido
	/**
	 *  Crea y arranca el proceso
	 *  @return Error generado en la ejecución del método
	 * */
	ProcessError start();

	/** Obtiene el estado del proceso */
	inline ProcessState getEstado() const {
		return state;
	}

	/** Retorna el PID del proceso */
	inline pid_t getPID() const {
		return bcp.pid;
	}

	/** Despierta al proceso 	 */
	inline void despertar() {
		kill(bcp.pid, SIG_RUN);
	}

	/** Asigna el pid
	 *
	 * @param pid Pid a asignar
	 */
	inline void setPid(pid_t pid) {
		this->bcp.pid = pid;
	}

	/** Retorna el BCP **/
	inline BCP getBCP() const{
		return bcp;
	}


	/** Agrega un bloqueo al vector de bloqueos
	 *
	 * @param bloqueo Bloqueo a agregar
	 */
	void addBloqueo(Bloqueo bloqueo);

	/** Agrega un bloqueo al vector de bloqueos (Análogo a addBloqueo);
	 *
	 * @param bloqueo Bloqueo a agregar
	 */
	Proceso& operator <<(Bloqueo bloqueo);

private:
	/**  Se ejecuta cuando el hijo finaliza su ejecución */
	static void hijoFinalizado(int);

	/** Despierta al proceso */
	static void despertador(int);

	/** Bloquea una señal
	 *
	 * @param signal Señal a bloquear
	 * @return La mascara de señales original
	 *
	 * @details Para bloquear las señales se modifica la máscara de mensajes.
	 * 			Si se recibe la señal bloqueada, en cualquier intervalo de tiempo,
	 * 			esta será lanzada al momento de activarla de nuevo.
	 * 			Este m'etodo se utiliza para evitar perdida de señales
	 */
	sigset_t bloquearSennal(int signal);

	/** Bloquea una señal
	 *
	 * @param signal Señal a bloquear
	 *
	 * @details Para bloquear las se;ales se modifcan la m;ascara de mensjaes.
	 * 			Cuando esta est'a activa
	 *
	 */
	void activarSennal();


protected:

	/** Inicializa los atributos
	 *
	 *  @param bcp BCP a asignar
	 */
	void _inicializar(BCP bcp);

	/** Pausa el proceso
	 *
	 *  @note Solo se debe usar dentro del método run()
	 */
	inline void pausar() {
		pause();
	}

	/** Método que ejecutará la rutina del proceso
	 *
	 * @warning La clase heredada no debe llamar a este método, solo implementarlo
	 * @note Originalmente era un método virtual puro, pero ya no se adaptaria al
	 *       modelo del sistema actual
	 */
	void run(){}

	/** Manejador de mensajes que permite la comunicación con el proceso remoto
	 *  a partir del envio de mensajes
	 *
	 * @param unused
	 */
	static void remoteHandler(int);

	/** Bloque de cotrol de proceso **/
	BCP bcp;

	/** Estado del proceso */
	ProcessState state;

	/** Permitirá la ejecución del métodos estáticos en el proceso remoto.
	 *
	 * Se utiliza porque no se puede asociar una señal con un método de instancia.
	 * Existirá un único _procesoActual por cada proceso remoto.
	 * */
	static Proceso *_procesoActual;

	/** Clave para acceder a los recursos compartidos **/
	static key_t key;

	/** Identificador de la cola **/
	static int idCola;

	/** Mascara de origen **/
	static sigset_t orig_mask;
};


#endif /* PROCESO_H_ */
