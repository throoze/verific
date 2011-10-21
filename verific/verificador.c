/**
 ****************************************************************************
 * @file verificador.c                                                      *
 * @brief PROYECTO 1: Aplicacion para la verificación de cambios en         *
 *        directorios.                                                      *
 *                                                                          *
 *   Programa trabajador, encargado de realizar la conexión con un solo di- *
 * rectorio remoto, y monitorizar los cambios que ocurran en él.            *
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
#include "verificador.h"


void pauseHandler() {
  while(conectado) {}
  pausado = TRUE;
  remaining = alarm(0);
  pause();
}

void continueHandler() {
  pausado = FALSE;
  alarm(remaining);
}

void killHandler() {
  free(directorio);
  hdestroy_r(registrados);
  exit(0);
}

int connection() {
  struct in_addr inaddr;
  struct hostent *hostent;
  int sock;
  struct sockaddr_in address;
  conectado = TRUE;
  if (inet_aton(host->domain, &inaddr)) {
    hostent = gethostbyaddr((char *) &inaddr, sizeof(inaddr), AF_INET);
  } else {
    hostent = gethostbyname(host->domain);
  }
  if (!hostent) {
    fprintf(stderr,"verific: verificador: Error tratando de resolver el hostname %s\n",host->domain);
    exit(1);
  }
  if(( sock = socket (PF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr,"verific: verificador: Error tratando de crear el socket\n");
    exit(1);
  }
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  /* Toma la primera direcci'on IP asociada a este hostname */
  memcpy(&address.sin_addr, hostent->h_addr_list[0], sizeof(address.sin_addr));
  if (connect(sock, (struct sockaddr *)&address, sizeof(address))) {
    fprintf(stderr,"verific: verificador: Error tratando de conectarse al dominio %s\n",host->domain);
    exit(1);
  }
  return sock;
}


List *makeRequest() {
  char *request = (char *) xmalloc(sizeof(directorio) + 1 + 4 + 10);
  sprintf(request,"GET %s HTTP/1.0 \r\n\r\n",directorio);
  int sock = connection();
  if (write(sock, request, sizeof(request)) != sizeof(request)) {
    fprintf(stderr,"verific: verificador: Error tratando de conectarse al dominio %s\n",host->domain);
    exit(1);
  }
  List *lista = newList();
  FILE *fileSock = fdopen(sock, "w+");
  if (fileSock == NULL) {
        perror("verific: verificador: Error abriendo el socket\n");
        exit(1);
  }
  char line[2048];
  while (fgets(line, 2040, fileSock) != NULL){
    fprintf(stderr,"%s",line);
  }

  close(sock);
  conectado = FALSE;
  return NULL;
}

Arch *parser(char *responseLine) {
  return NULL;
}

void procesar(List *recibidos){

}

void alarmHandler() {
  List *recibidos = makeRequest();
  procesar(recibidos);
  alarm(t);
}

void buildHost(){
  char * copy = (char *)xmalloc(strlen(directorio)+1);
  strcpy(copy,directorio);
  host->uri = directorio;
  char *primero = strtok(copy,"/");
  if (strcmp(primero,"http:") != 0) {
    host->domain = primero;
  } else {
    host->domain = strtok(NULL,"/");
  }
}

/**
 * Programa principal
 *
 * @param argc Número de parametros con el que se hizo la invocación
 *             programa.
 * @param argv Valores de los argumentos pasados al programa por línea de
 *             comandos. Recibe como primer parámetro el URL del directorio a
 *             verificar, y como segundo parámetro el número de segundos entre
 *             cada verificación.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 */
int main (int argc, char **argv) {
  // Inicializaciones:
  t = atoi(argv[2]);
  directorio = (char *) xmalloc((strlen(argv[1])+1) * sizeof(char));
  strcpy(directorio,argv[1]);
  signal(SIGKILL,killHandler);
  signal(SIGUSR1,pauseHandler);
  signal(SIGUSR2,continueHandler);
  /*
  int err;
  if (!(err = hcreate_r(15,registrados))) {
    fprintf(stderr,"verific: verificador[%d]: Problema interno creando estructura de almacenamiento.\n",getpid());
    fprintf(stderr,"error: %d\n",err);
    exit(1);
  }
  */
  host = (Host *) xmalloc(sizeof(Host));
  buildHost();
  // Inicio del timeout:
  alarm(t);

  // Ciclo infinito para esperar la señal de alarma.
  while(TRUE){};

  // Liberación de espacio usado:
  free(directorio);
  hdestroy_r(registrados);
  return 0;
}
