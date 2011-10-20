/**
 ****************************************************************************
 * @file expreg.h                                                           *
 * @brief Librería que define operaciones que facilitan el uso de la libre- *
 *        ría estándar de unix de expresiones regulares. (HEADER)           *
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
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#define FALSE 0
#define TRUE 1
#endif

#include <regex.h>

#ifndef UTL
#define UTL
#include "util.h"
#endif

/**
 * @brief Devuelve TRUE si el parámetro 'string' es reconocido por el patrón
 * 'pattern'.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 *
 * @param string Cadena de caracteres que será comparada contra el patrón.
 * @param pattern Cadena de caracteres que representa un patrón o expresión
 *                regular POSIX.
 * @return 0 en caso de que 'string' sea reconocida por 'pattern'; un valor di-
 *         ferente de cero en caso contrario. Ver las funciones referenciadas en
 *         el manual de c de GNU para una lista de los valores diferentes de ce-
 *         ro que podría retornar esta función.
 * @see regcomp()
 * @see regexec()
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 */
int matches(char *string, char *pattern);

/**
 * Interactúa con la librería de expresiónesregulares de c, para construir un
 * mensaje de error, a partir de una expresión regular y un código de salida.
 * @param errcode Código de error retornado por las funciones de la ibrería
 *                regexp.h
 * @param compiled Estructura con la espresión gregular compilada que generó el
 *                 error
 * @author Manual de C de GNU:
 *     http://www.gnu.org/s/hello/manual/libc/Regexp-Cleanup.html#Regexp-Cleanup
 */
char *get_regerror (int errcode, regex_t *compiled);
