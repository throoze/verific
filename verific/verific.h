/**
 ****************************************************************************
 * @file verific.h                                                          *
 * @brief PROYECTO 1: Aplicacion para la verificación de cambios en         *
 *        directorios.                                                      *
 *                                                                          *
 * Encabezado del programa principal del proyecto.                          *
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

#include "almacenamiento.h"
#include "expreg.h"
#ifndef UTL
#define UTL
#include "util.h"
#endif


///Expresión regular POSIX que unifica con un URL válido.
char *URL_REGEXP = "^http\://[a-zA-Z0-9_-]*\\.?[a-zA-Z0-9_-]+(\\.(com|edu|gov|int|mil|net|org|biz|arpa|info|name|pro|aero|coop|museum|ve|[a-zA-Z]{2}(:[0-9]{1,5})?){1})(/[a-zA-Z0-9:#@%/;$()~_?\+-=\\\.&]*|/?)$";
// No utilizo esta, porque aqui sólo usaremos el protocolo http.
//char *URL_REGEXP = "^(https?|ftp|gopher|telnet|file|notes|ms-help)\://[a-zA-Z0-9_-]*\\.?[a-zA-Z0-9_-]+(\\.(com|edu|gov|int|mil|net|org|biz|arpa|info|name|pro|aero|coop|museum|ve|[a-zA-Z]{2}(:[0-9]{1,5})?){1})(/[a-zA-Z0-9:#@%/;$()~_?\+-=\\\.&]*|/?)$";

///Número de directorios a verificar.
int n = 1;

///Arreglo de directorios a monitorizar.
char **directorios;


/**
 * Función que imprime en pantalla un mensaje de ayuda con la sintaxis,
 * y la descripción de los parámetros de invocación del programa.
 */
void mensaje_ayuda ();

/**
 * Se encarga de procesar y validar los argumentos entrados por linea de
 * comandos.
 *
 * @param argc Número de parametros con el que se hizo la invocación
 *             programa.
 * @param argv Valores de los argumentos pasados al programa por línea de
 *             comandos. Los valores válidos corresponden con lo especificado en
 *             la descripción del proyecto.
 * @param t Intervalo de tiempo, en segundos, a transcurrir entre cada
 *          verificación.
 * @param aVerificar String que contendrá el nombre del directorio a verificar o
 *                   el archivo a leer, según sea el resultado del procesamiento
 *                   de parámetros.
 * @param dir_especificado TRUE en caso de que se haya especificado el URL de un
 *                         directorio a verificar; FALSE en caso contrario.
 * @param arch_especificado TRUE en caso de que se haya especificado el nombre
 *                          un archivo a leer; FALSE en caso contrario.
 */
void procesarArgumentos(int argc, char **argv, int *t, char **aVerificar,
                        int *dir_especificado, int *arch_especificado);

/**
 * En caso de poder, lee el archivo 'file', lo valida y prepara una estructura
 * de lista, con los URL's leidos del archivo, la cual retorna.
 *
 * @param file Nombre del archivo a leer.
 * @return Apuntador a lista con los URL's a monitorizar.
 */
ListaStr *leerArchivo(char * file);
