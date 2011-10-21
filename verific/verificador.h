/**
 ****************************************************************************
 * @file verificador.h                                                      *
 * @brief PROYECTO 1: Aplicacion para la verificación de cambios en         *
 *        directorios.                                                      *
 *                                                                          *
 *   Programa trabajador, encargado de realizar la conexión con un solo di- *
 * rectorio remoto, y monitorizar los cambios que ocurran en él. (HEADER)   *
 *                                                                          *
 * Universidad Nacional Experimental Simón Bolívar                          *
 * Departamento de Computación y Tecnología de la Información               *
 * Redes de computadoras 1                                                  *
 * Trimestre Septiembre - Diciembre 2011                                    *
 * Profesores: Ricardo Gonzales, Carlos Gómez                               *
 * PROYECTO 1: Aplicacion para la verificación de cambios en directorios    *
 *             remotos.                                                     *
 * @author Jerilyn Goncalves, 05-38242                                      *
 * @author Victor de Ponte, 05-38087                                        *
 * @version 1.0                                                             *
 * @date 10/14/2011                                                         *
 ****************************************************************************/

#ifndef STD
#define STD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#define TRUE 1
#define FALSE 0
#endif

#ifndef PROCS
#define PROCS
#include <sys/wait.h>
#endif

#ifndef SOCKETS
#define SOCKETS
#define PORT 80
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#ifndef SGNL
#define SGNL
#include <signal.h>
#endif

#ifndef HASHTAB
#define HASHTAB
#define _GNU_SOURCE
#include <search.h>
#endif

#include "almacenamiento.h"
#include "expreg.h"
#ifndef UTL
#define UTL
#include "util.h"
#endif

/// Directorio a monitorizar:
char *directorio;

/// Intervalo de tiempo entre cada verificación:
int t;

/// Indicador de pausa:
int pausado;

/// Indicador de conexión:
int conectado = FALSE;

/// Tiempo restante para la siguiente verificación:
int remaining;

/**
 * Estructuras asociadas a la tabla de hash que almacena los archivos en en el
 * directorio monitorizado.
 */
struct hsearch_data *registrados;
ENTRY query;
ENTRY *result;


/// Estructura que almacena una la dirección dividida en ip, host y URI.
typedef struct {
  char *domain;
  char *uri;
  char *ip;
} Host;

/// Almacena la info del host a consultar:
Host *host;

/// Patrón para reconocer archivos en la respuesta del servidor.
char *pattern = "";
