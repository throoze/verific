/**
 ****************************************************************************
 * @file almacenamiento.h                                                   *
 * @brief Librería que define estructuras de almacenamiento de datos, y     *
 *        operaciones aplicadas sobre dichas estructuras. (HEADER)          *
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

#ifndef UTL
#define UTL
#include "util.h"
#endif

#ifndef EDG
#define EDG
#include <limits.h>
#endif

/*----------------------------------------------------------------------------*/

/*Definición del tipo ListaStr.*/

/**
 * Clasica lista de elementos. Es una lista de apuntadores que almacena char *.
 * (String)
 */
typedef struct cajaStr CajaStr;

struct cajaStr {
  char *data;
  int pos;
  CajaStr *sig,*ant;
};

typedef struct {
  CajaStr *head,*tail;
  int size;
} ListaStr;
/*FIN del tipo ListaStr.*/

/*INICIO Funciones y Procedimientos referentes al tipo ListaStr*/
/**
 * Crea una nueva CajaStr, reservando la memoria necesaria para ello.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @return Un nuevo apuntador a CajaStr vacía.
 */
CajaStr *newCajaStr();

/**
 * Crea una nueva lista vacía, reservando la memoria necesaria para ello.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @return Un nuevo apuntador a una lista vacía.
 */
ListaStr *newListaStr();


/**
 * Inserta el elemento 'elem' en la Lista '*list'
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param list apuntador a la Lista donde se desea hacer la inserción.
 * @param elem elemento a insertar en la Lista.
 * @return Un entero que indica el estado de la inserción; 0 si fue realizada
 *         con éxito, 1 en caso contrario.
 */
int addLS(ListaStr *list, char *elem);

/**
 * Elimina el elemento 'elem' en la Lista '*list'
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param list apuntador a la Lista donde se desea hacer la eliminación.
 * @param elem elemento a eliminar de la Lista.
 */
void deleteLS(ListaStr *list,  char *elem);


/**
 * Devuelve el elemento en la posición pos.
 * Retorna en la variable 'ans' el elemento almacenado en la posición 'posi'.
 * de no existir un elemento en esa posicion, asigna NULL a 'ans'.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param list Lista a consultar.
 * @param posi Posición del elemento solicitado.
 * @param ans  Apuntador a la salida de esta funcion.
 */
void getLS(ListaStr *list, int posi, char *ans);


/**
 * Devuelve un arreglo de String conteniendo los elementos de la lista 'list'
 * en el mismo orden en que estaban almacenados.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param list Lista a transformar en arreglo.
 * @return Un arreglo de String que contiene los elementos de 'lista' en el
 *         mismo orden en que estaban almacenados.
 */
char **LSToArray(ListaStr *list);

/**
 * Dice si un elemento 'elem' está actualmente o no en la Lista '*list'.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param list Apuntador a la Lista donde se desea hacer la búsqueda.
 * @param elem Elemento a buscar en la Lista.
 * @return Un entero que indica el estado de la búsqueda; 1 si se encontró el
 *         elemento, 1 en caso contrario.
 */
int isInLS(ListaStr *list, char *elem);


/**
 * Imprime en la salida estándar la ListaInt 'lista'.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param lista ListaInt a imprimir.
 */
void LSprint(ListaStr *lista);

/**
 * Devuelve el primer elemento de la lista, y lo elimina de ésta.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param list Lista a consultar.
 * @return El primer elemento de la lista, o NULL en caso de que sea
 *         una lista vacía.
 */
char *getFirstLS(ListaStr *list);

/**
 * Devuelve el último elemento de la lista, y lo elimina de ésta.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param list Lista a consultar.
 * @return El último elemento de la lista, o NULL en caso de que sea
 *         una lista vacía.
 */
char *getLastLS(ListaStr *list);


/**
 * Se encarga de devolver una ListaInt a su estado original vacía, liberando la
 * memoria consumida por ésta.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 * @param lote Un apuntador a la ListaInt que se desea liberar.
 * @return 0 si se completó la limpieza con éxito, 1 en caso contrario.
 */
int LSLiberar(ListaStr *lista);

/*FIN Funciones y Procedimientos referentes al tipo ListaStr*/

/*----------------------------------------------------------------------------*/

/*FIN DEL ARCHIVO (EOF)*/
