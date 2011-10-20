/**
 ****************************************************************************
 * @file util.c                                                             *
 * @brief Librería que define operaciones útiles en general.                *
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

#include "util.h"

void *xmalloc(size_t size) {
  register void *value = malloc(size);
  if (value == 0) {
    printf("Memoria Virtual Agotada!");
    exit(-1);
  }
  return value;
}
