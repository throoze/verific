/**
 ****************************************************************************
 * @file verific.c                                                          *
 * @brief PROYECTO 1: Aplicacion para la verificación de cambios en         *
 *        directorios.                                                      *
 *                                                                          *
 * Programa principal del proyecto.                                         *
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

#include "verific.h"

///Almacena la lista de directorios a monitorizar.
ListaStr *directorios;


void mensaje_ayuda ()
{

    printf("\nSINTAXIS:\n");
    printf("\tverific [-t num_segundos] [-d directorio] [-a archivo]\n");
    printf("DONDE:\n");
    printf("\tnum_segundos:\tValor entero que representa el numero de segundos que\n");
    printf("\t\t\tdeben transcurrir entre dos revisiones.\n\n");
    printf("\tdirectorio:\tEspecifica el URL del directorio a\n\t\t\tmonitorizar.\n\n");
    printf("\tarchivo:\tArchivo que contendrá los URL de los directorios a\n\t\t\tmonitorizar.\n\n");
    printf("\tLas banderas entre corchetes ([]) son opcionales.\n");
    printf("\tDebe especificarse al menos la opción -d o la opción -a. ");
    printf("En caso de que\n\tlas opciónes -d y -a sean especificadas simultanea");
    printf("mente, se verificará\n\tsolamente el directorio que esta especi");
    printf("ficado en el parámetro -d.\n\tSi el parámetro -t no es especificado, ");
    printf("se puede asumir un valor por\n\tdefecto de 30 segundos.\n");
}

void procesarArgumentos(int argc, char **argv, int *t, char **aVerificar,
                        int *dir_especificado, int *arch_especificado) {
  // tests triviales
  if (argc==1) {
    printf("verific: Usted no especificó ningún parámetro.\n");
    mensaje_ayuda();
    exit(-1);
  } else if (argc < 3) {
    printf("verific: Se han especificado parámetros insuficientes.\n");
    mensaje_ayuda();
    exit(-1);
  } else if (7 < argc) {
    printf("verific: Se han especificado parámetros de más.\n");
    mensaje_ayuda();
    exit(-1);
  }

  // Procesamiento:
  *t = 30; // Valor por defecto
  int opt; // Contenedor de la opción a ser probada en el switch-case
  char *directorio;
  char *archivo;
  while ((opt = getopt (argc, argv, "t:d:a:")) != -1) {
    switch (opt)
      {
      case 't':
        //*t = atoi(optarg);
        *t = strtol(optarg, (char **) NULL, 10);
        break;
      case 'd':
        *dir_especificado = TRUE;
        // VERIFICAR QUE, EN EFECTO, SEA UN URL
        directorio = (char *) malloc((strlen(optarg) + 1) * sizeof(char));
        strcpy(directorio,optarg);
        break;
      case 'a':
        *arch_especificado = TRUE;
        // VERIFICAR QUE NO COMIENZE POR '-' (QUE SEA LA SIGUIENTE OPCIÓN)
        archivo = (char *) malloc((strlen(optarg) + 1) * sizeof(char));
        strcpy(archivo,optarg);
        break;
      case ':' :
      case '?':
        if (optopt == 't' || optopt == 'd' || optopt == 'a') {
          fprintf(stderr, "verific: La opción -%c requiere de un argumento.\n",optopt);
        } else if (isprint(optopt)) {
          fprintf (stderr, "verific: Opción desconocida '-%c'.\n", optopt);
        } else {
          fprintf (stderr,
                   "verific: Caracter de opción desconocido '\\x%x'.\n",
                   optopt);
        }
      default:
        mensaje_ayuda();
        exit(-1);
      }
  }

  if (!(*dir_especificado || *arch_especificado)) {
    printf("verific: Debe especificar al menos la opción -d o la opción -a.\n");
    mensaje_ayuda();
    exit(-1);
  }

  if (*t <= 0) {
    printf("verific: El intervalo de tiempo debe ser un entero positivo (mayor que cero).\n");
    mensaje_ayuda();
    exit(-1);
  }

  if (*dir_especificado) {
    *aVerificar = (char *) malloc((strlen(directorio) + 1) * sizeof(char));
    strcpy(*aVerificar,directorio);
  } else if (*arch_especificado) {
    *aVerificar = (char *) malloc((strlen(archivo) + 1) * sizeof(char));
    strcpy(*aVerificar,archivo);
  }

  if (*dir_especificado) {
    free(directorio);
  }
  if (*arch_especificado) {
    free(archivo);
  }
}

/**
 * En caso de poder, lee el archivo 'file', lo valida y prepara una estructura
 * de lista, con los URL's leidos del archivo, la cual retorna.
 *
 * @param file Nombre del archivo a leer.
 * @return Apuntador a lista con los URL's a monitorizar.
 */
ListaStr *leerArchivo(char * file) {

}

/**
 * Programa principal
 *
 * @param argc Número de parametros con el que se hizo la invocación
 *             programa.
 * @param argv Valores de los argumentos pasados al programa por línea de
 *             comandos. Los valores válidos corresponden con lo especificado en
 *             la descripción del proyecto.
 */
int main (int argc, char **argv) {

  ///Tiempo en segundos entre cada verificación. Valor por defecto: 30s
  int t;

  ///Número de directorios a verificar.
  int n = 1;

  /**
   * TRUE si se especificó un directorio por linea de comandos;
   * FALSE en caso contrario.
   */
  int dir_especificado = 0;

  /**
   * TRUE si se especificó un archivo por linea de comandos;
   * FALSE en caso contrario.
   */
  int arch_especificado = 0;

  /**
   * Contendra el nombre ya sea del único directorio a verificar, o del archivo
   * a leer el cual contendrá un URL por linea de un directorio a modificar.
   */
  char *aVerificar;

  procesarArgumentos(argc,argv,&t,&aVerificar,&dir_especificado,
                     &arch_especificado);

  int sockfd;
  struct sockaddr_in serveraddr;

  if (dir_especificado) {
    directorios = newListaStr();
    addLS(directorios,aVerificar);
  } else {
    directorios = leerArchivo(aVerificar);
  }


























  printf("El intervalo de tiempo esta setteado a %d segundos\n",t);
  if (dir_especificado){
    printf("Se especificó un URL a ser verificado, de nombre %s\n", aVerificar);
  } else if (arch_especificado) {
    printf("Se especificó un archivo para ser leido, de nombre %s\n", aVerificar);
  }

  LSLiberar(directorios);
  return 0;
}
