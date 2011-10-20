/**
 ****************************************************************************
 * @file expreg.c                                                           *
 * @brief Librería que define operaciones que facilitan el uso de la libre- *
 *        ría estándar de unix de expresiones regulares.                    *
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

#include "expreg.h"

int matches(char *string, char *pattern){
  regex_t *expreg = (regex_t *) xmalloc(sizeof(regex_t));
  int comp;
  if (!(comp = regcomp(expreg,pattern,REG_EXTENDED))) {
    //int ans = regexec(expreg, string,0, NULL,REG_NOTBOL|REG_NOTEOL);
    int ans = regexec(expreg, string,0, NULL,0);
    regfree (expreg);
    free(expreg);
    if ( ans == REG_ESPACE) {
      printf("verific: Ha ocurrido un error:\nverific:%s",get_regerror(ans,expreg));
      exit(-1);
    }
    //printf("\nEl resultado de comparar el string '%s'\ncontra el patrón '%s', es: %d\n\n",string,pattern,ans);
    return ans;
  } else {
    printf("verific: Ha ocurrido un error:\nverific:%s",get_regerror(comp,expreg));
    exit(-1);
  }
  return -1;
}

char *get_regerror(int errcode, regex_t *compiled) {
  size_t length = regerror (errcode, compiled, NULL, 0);
  char *buffer = xmalloc (length);
  (void) regerror (errcode, compiled, buffer, length);
  return buffer;
}
