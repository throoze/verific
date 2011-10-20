/**
 ****************************************************************************
 * @file util.h                                                             *
 * @brief Librería que define operaciones útiles en general. (HEADER)       *
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

/**
 * Realiza la llamada al sistema de reserva de memoria y chequea que el espacio
 * haya sido, en efecto, reservado. /en caso de que haya ocurrido un error, de-
 * vuelve un mensaje de error y termina el programa.
 *
 * @param size Tamaño de memoria en bytes a ser reservado.
 * @author basado en la función xmalloc del manual de c de GNU:
 *   http://www.gnu.org/s/hello/manual/libc/Malloc-Examples.html#Malloc-Examples
 */
void *xmalloc(size_t size);
