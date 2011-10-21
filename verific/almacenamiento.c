/**
 ****************************************************************************
 * @file almacenamiento.c                                                   *
 * @brief Librería que define estructuras de almacenamiento de datos, y     *
 *        operaciones aplicadas sobre dichas estructuras.                   *
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

#include "almacenamiento.h"

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

#ifndef UTL
#define UTL
#include "util.h"
#endif

#ifndef EDG
#define EDG
#include <limits.h>
#endif

/*----------------------------------------------------------------------------*/

/*INICIO Funciones y Procedimientos referentes al tipo ListaStr*/
CajaStr *newCajaStr() {
  CajaStr *nueva = (CajaStr *) xmalloc(sizeof(CajaStr));
  if (nueva != NULL) {
    nueva->sig = nueva->ant = NULL;
    nueva->pos = 0;
    return nueva;
  } else {
    fprintf(stderr, "newCajaStr: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

ListaStr *newListaStr() {
  ListaStr *nueva = (ListaStr *) xmalloc(sizeof(ListaStr));
  if (nueva != NULL) {
    nueva->head = nueva->tail = NULL;
    nueva->size = 0;
    return nueva;
  } else {
    fprintf(stderr, "newListaStr: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

int addLS(ListaStr *list, char *elem) {
  CajaStr *nueva = newCajaStr();
  nueva->data = elem;
  if (list->head != NULL && list->tail != NULL) {
    list->tail->sig = nueva;
    nueva->ant = list->tail;
    nueva->sig = NULL;
    list->tail = nueva;
    nueva->pos = nueva->ant->pos + 1;
  } else {
    list->head = list->tail = nueva;
    nueva->pos = 0;
  }
  list->size++;
  nueva = NULL;
  return 0;
}

void deleteLS(ListaStr *list,  char *elem) {
  CajaStr *aux = list->head;
  while (aux) {
    if (strcmp(aux->data,elem) == 0) {
      if (list->size == 1) {
        free(aux);
        aux = list->head = list->tail = NULL;
        return;
      }
      if (aux->ant) {
        aux->ant->sig = aux->sig;
      } else {
        list->head = aux->sig;
      }
      if (aux->sig) {
        aux->sig->ant = aux->ant;
      } else {
        list->tail = aux->ant;
      }
      aux->ant = aux->sig = NULL;
      free(aux);
      aux = NULL;
      list->size--;
      return;
    }
    aux = aux->sig;
  }
  return;
}

void getLS(ListaStr *list, int posi, char *ans) {
  CajaStr *aux = list->head;
  while (aux && aux->pos != posi && aux->sig) {
    aux = aux->sig;
  }
  if (aux) {
    if (aux->pos == posi) {
      ans = aux->data;
    } else {
      ans = NULL;
    }
  }
}

char **LSToArray(ListaStr *list) {
  char **arr = (char **) xmalloc(list->size * sizeof(char *));
  CajaStr *aux = list->head;
  register int i = 0;
  while (aux) {
    arr[i] = aux->data;
    aux = aux->sig;
    i++;
  }
  return arr;
}

int isInLS(ListaStr *list, char *elem) {
  CajaStr *aux = list->head;
  while (aux) {
    if (strcmp(aux->data,elem) == 0) {
      return TRUE;
    }
    aux = aux->sig;
  }
  return FALSE;
}

void LSprint(ListaStr *lista) {
  CajaStr *aux = lista->head;
  printf("|-----TAMAÑO = %d-----|\n",lista->size);
  printf("|-------INICIO-------|\n");
  while (aux) {
    printf("%s\n", aux->data);
    aux = aux->sig;
  }
  printf("|--------FIN---------|\n");
}

char *getFirstLS(ListaStr *list) {
  char *ans = NULL;
  if (list->size != 0 && list->head) {
    ans = list->head->data;
    CajaStr *aux = list->head;
    if (list->size == 1) {
      list->head = list->tail = NULL;
      free(aux);
      list->size--;
    } else {
      if (list->head->sig) {
        list->tail = list->head->sig;
        free(aux->data);
        free(aux);
        aux = NULL;
        list->size--;
      } else {
        return ans;
      }
    }
  }
  return ans;
}

char *getLastLS(ListaStr *list) {
  char *ans = NULL;
  if (list->size != 0 && list->tail) {
    ans = list->tail->data;
    CajaStr *aux = list->tail;
    if (list->size == 1) {
      list->head = list->tail = NULL;
      free(aux);
      list->size--;
    } else {
      if (list->tail->ant) {
        list->tail = list->tail->ant;
        free(aux->data);
        free(aux);
        aux = NULL;
        list->size--;
      } else {
        return ans;
      }
    }
  }
  return ans;
}

int LSLiberar(ListaStr *lista) {
  while (lista->size > 0) {
    getFirstLS(lista);
  }
  if (lista->size == 0)
    return 0;
  else
    return 1;
}

/*FIN Funciones y Procedimientos referentes al tipo ListaStr*/

/*INICIO Funciones y Procedimientos referentes al tipo List*/
Caja *newCaja() {
  Caja *nueva = (Caja *) xmalloc(sizeof(Caja));
  if (nueva != NULL) {
    nueva->sig = nueva->ant = NULL;
    nueva->pos = 0;
    return nueva;
  } else {
    fprintf(stderr, "newCaja: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

List *newList() {
  List *nueva = (List *) xmalloc(sizeof(List));
  if (nueva != NULL) {
    nueva->head = nueva->tail = NULL;
    nueva->size = 0;
    return nueva;
  } else {
    fprintf(stderr, "newList: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

int add(List *list, Arch *elem) {
  Caja *nueva = newCaja();
  nueva->data = elem;
  if (list->head != NULL && list->tail != NULL) {
    list->tail->sig = nueva;
    nueva->ant = list->tail;
    nueva->sig = NULL;
    list->tail = nueva;
    nueva->pos = nueva->ant->pos + 1;
  } else {
    list->head = list->tail = nueva;
    nueva->pos = 0;
  }
  list->size++;
  nueva = NULL;
  return 0;
}

void delete(List *list,  Arch *elem) {
  Caja *aux = list->head;
  while (aux) {
    if (strcmp(aux->data->name,elem->name) == 0) {
      if (list->size == 1) {
        free(aux);
        aux = list->head = list->tail = NULL;
        return;
      }
      if (aux->ant) {
        aux->ant->sig = aux->sig;
      } else {
        list->head = aux->sig;
      }
      if (aux->sig) {
        aux->sig->ant = aux->ant;
      } else {
        list->tail = aux->ant;
      }
      aux->ant = aux->sig = NULL;
      free(aux);
      aux = NULL;
      list->size--;
      return;
    }
    aux = aux->sig;
  }
  return;
}

void get(List *list, int posi, Arch *ans) {
  Caja *aux = list->head;
  while (aux && aux->pos != posi && aux->sig) {
    aux = aux->sig;
  }
  if (aux) {
    if (aux->pos == posi) {
      ans = aux->data;
    } else {
      ans = NULL;
    }
  }
}

Arch **ToArray(List *list) {
  Arch **arr = (Arch **) xmalloc(list->size * sizeof(Arch *));
  Caja *aux = list->head;
  register int i = 0;
  while (aux) {
    arr[i] = aux->data;
    aux = aux->sig;
    i++;
  }
  return arr;
}

int isIn(List *list, Arch *elem) {
  Caja *aux = list->head;
  while (aux) {
    if (strcmp(aux->data->name,elem->name) == 0) {
      return TRUE;
    }
    aux = aux->sig;
  }
  return FALSE;
}

Arch *getFirst(List *list) {
  Arch *ans = NULL;
  if (list->size != 0 && list->head) {
    ans = list->head->data;
    Caja *aux = list->head;
    if (list->size == 1) {
      list->head = list->tail = NULL;
      free(aux);
      list->size--;
    } else {
      if (list->head->sig) {
        list->tail = list->head->sig;
        free(aux->data);
        free(aux);
        aux = NULL;
        list->size--;
      } else {
        return ans;
      }
    }
  }
  return ans;
}

Arch *getLast(List *list) {
  Arch *ans = NULL;
  if (list->size != 0 && list->tail) {
    ans = list->tail->data;
    Caja *aux = list->tail;
    if (list->size == 1) {
      list->head = list->tail = NULL;
      free(aux);
      list->size--;
    } else {
      if (list->tail->ant) {
        list->tail = list->tail->ant;
        free(aux->data);
        free(aux);
        aux = NULL;
        list->size--;
      } else {
        return ans;
      }
    }
  }
  return ans;
}

int listFree(List *lista) {
  while (lista->size > 0) {
    getFirst(lista);
  }
  if (lista->size == 0)
    return 0;
  else
    return 1;
}

/*FIN Funciones y Procedimientos referentes al tipo List*/

/*----------------------------------------------------------------------------*/

/*FIN DEL ARCHIVO (EOF)*/
