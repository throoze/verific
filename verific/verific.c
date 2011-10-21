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

void childHandler() {
  int childPid, childStatus;
  childPid = wait(&childStatus);
}

void mensaje_ayuda (int error) {
  char *usage = "\nSINTAXIS:\n\tverific [-t num_segundos] [-d directorio] [-a archivo]\nDONDE:\n\tnum_segundos:\tValor entero que representa el numero de segundos que\n\t\t\tdeben transcurrir entre dos revisiones.\n\n\tdirectorio:\tEspecifica el URL del directorio a\n\t\t\tmonitorizar.\n\n\tarchivo:\tArchivo que contendrá los URL de los directorios a\n\t\t\tmonitorizar.\n\n\tLas banderas entre corchetes ([]) son opcionales.\n\tDebe especificarse al menos la opción -d o la opción -a. En caso de que\n\tlas opciónes -d y -a sean especificadas simultaneamente, se verificará\n\tsolamente el directorio que esta especificado en el parámetro -d.\n\tSi el parámetro -t no es especificado, se puede asumir un valor por\n\tdefecto de 30 segundos.\n";
  if (error) {
    perror(usage);
  } else {
    printf("%s",usage);
  }
}

void ayuda_cli() {
  printf("\nCOMANDOS:\n");
  printf("\tp: Pausa\n");
  printf("\tc: Continuar\n");
  printf("\ts: Salir\n");
  printf("\th: Muestra esta ayuda\n\n");
  return;
}

void mens_despedida(){
  printf("#################################################\n");
  printf("#      _   _    _    ____  _______    _         #\n");
  printf("#     | | | |  / \\  |  __||__   __|  / \\        #\n");
  printf("#     | |_| | / _ \\  \\ \\     | |    / _ \\       #\n");
  printf("#     |  _  || |_| |  \\ \\    | |   | |_| |      #\n");
  printf("#     | | | ||  _  | __| |   | |   |  _  |      #\n");
  printf("#     |_| |_||_| |_||___/    |_|   |_| |_|      #\n");
  printf("#                                          _    #\n");
  printf("#     _      _   _  ____  _____   _____   | |   #\n");
  printf("#    | |    | | | |/  __|/  _  \\ /  _  \\  | |   #\n");
  printf("#    | |    | | | || |_  | | |_| | | | |  | |   #\n");
  printf("#    | |    | | | ||  _| | | ___ | | | |  |_|   #\n");
  printf("#    | |___ |  v  || |__ | ||_  || |_| |   _    #\n");
  printf("#    |_____| \\___/ \\____|\\_____/ \\_____/  |_|   #\n");
  printf("#                                               #\n");
  printf("#################################################\n");
  printf("\n");
  printf("\n");
  return;
}

void mens_pausado() {
  printf("#################################################\n");
  printf("#    ___    _    _  _   ___    _    __    ___   #\n");
  printf("#   |   |  / \\  | || | /  _\\  / \\  |  \\  / _ \\  #\n");
  printf("#   |  _| | ^ | | || | \\__\\  | ^ | | D || |_| | #\n");
  printf("#   |_|   |_|_|  \\__/  |___| |_|_| |__/  \\___/  #\n");
  printf("#                                               #\n");
  printf("#################################################\n");
  printf("#    PRESIONE LA TECLA 'C' PARA CONTINUAR...    #\n");
  printf("#      PRESIONE LA TECLA 'S' PARA SALIR...      #\n");
  printf("#################################################\n");
  printf("\n");
  printf("\n");
  return;
}

void mens_continuar(){
  printf("Continuando la verificación...\n");
  printf("\n");
  printf("\n");
  return;
}

void procesarArgumentos(int argc, char **argv, int *t, char **aVerificar,
                        int *dir_especificado, int *arch_especificado) {
  // tests triviales
  if (argc==1) {
    perror("verific: Usted no especificó ningún parámetro.\n");
    mensaje_ayuda(TRUE);
    exit(-1);
  } else if (argc < 3) {
    perror("verific: Se han especificado parámetros insuficientes.\n");
    mensaje_ayuda(TRUE);
    exit(-1);
  } else if (7 < argc) {
    perror("verific: Se han especificado parámetros de más.\n");
    mensaje_ayuda(TRUE);
    exit(-1);
  }
  // Procesamiento:
  *t = 30; // Valor por defecto
  int opt; // Contenedor de la opción a ser probada en el switch-case
  char *directorio;
  char *archivo;
  while ((opt = getopt (argc, argv, "ht:d:a:")) != -1) {
    switch (opt)
      {
      case 'h':
        mensaje_ayuda(FALSE);
        exit(0);
      case 't':
        //*t = atoi(optarg);
        *t = strtol(optarg, (char **) NULL, 10);
        break;
      case 'd':
        *dir_especificado = TRUE;
        int isURL = matches(optarg,URL_REGEXP);
        if (isURL == REG_NOMATCH) {
          perror("verific: El directorio especificado debe ser un URL válido.\n");
          mensaje_ayuda(TRUE);
          exit(-1);
        }
        directorio = (char *) xmalloc((strlen(optarg) + 1) * sizeof(char));
        strcpy(directorio,optarg);
        break;
      case 'a':
        *arch_especificado = TRUE;
        char *pattern = "^-[a-zA-Z]+$";
        int isNotOption = matches(optarg,pattern);
        if (!isNotOption) {
          perror("verific: La opción -a requiere de un argumento.\n");
          mensaje_ayuda(TRUE);
          exit(-1);
        }
        archivo = (char *) xmalloc((strlen(optarg) + 1) * sizeof(char));
        strcpy(archivo,optarg);
        break;
      case ':' :
      case '?':
        if (optopt == 't' || optopt == 'd' || optopt == 'a') {
          fprintf(stderr, "verific: La opción -%c requiere de un argumento.\n",optopt);
        } else if (isprint(optopt)) {
          fprintf(stderr, "verific: Opción desconocida '-%c'.\n", optopt);
        } else {
          fprintf(stderr,"verific: Caracter de opción desconocido '\\x%x'.\n",
                  optopt);
        }
      default:
        mensaje_ayuda(TRUE);
        exit(-1);
      }
  }
  if (!(*dir_especificado || *arch_especificado)) {
    perror("verific: Debe especificar al menos la opción -d o la opción -a.\n");
    mensaje_ayuda(TRUE);
    exit(-1);
  }
  if (*t <= 0) {
    perror("verific: El intervalo de tiempo debe ser un entero positivo (mayor que cero).\n");
    mensaje_ayuda(TRUE);
    exit(-1);
  }
  if (*dir_especificado) {
    *aVerificar = (char *) xmalloc((strlen(directorio) + 1) * sizeof(char));
    strcpy(*aVerificar,directorio);
  } else if (*arch_especificado) {
    *aVerificar = (char *) xmalloc((strlen(archivo) + 1) * sizeof(char));
    strcpy(*aVerificar,archivo);
  }
  if (*dir_especificado) {
    free(directorio);
  }
  if (*arch_especificado) {
    free(archivo);
  }
}

// HACER ESTO!!!!
ListaStr *leerArchivo(char * file) {
  printf("verific: La funcionalidad de leer una lista de directorios desde un archivo no esta implementada todavía.\nel programa terminará...\n");
  exit(-1);
  return NULL;
}

char getChar() {
  system("stty -echo raw");
  char input = getchar();
  //system("stty cooked");
  system("stty sane");
  return input;
}

void matarHijos() {
  register int i;
  for (i = 0; i < n; i++) {
    kill(pids[i],SIGKILL);
  }
  return;
}

void pausarHijos() {
  register int i;
  for (i = 0; i < n; i++) {
    kill(pids[i],SIGUSR1);
  }
  return;
}

void continuarHijos() {
  register int i;
  for (i = 0; i < n; i++) {
    kill(pids[i],SIGUSR2);
  }
  return;
}

/**
 * Programa principal
 *
 * @param argc Número de parametros con el que se hizo la invocación
 *             programa.
 * @param argv Valores de los argumentos pasados al programa por línea de
 *             comandos. Los valores válidos corresponden con lo especificado en
 *             la descripción del proyecto.
 *
 * @author Jerilyn Goncalves, 05-38242
 * @author Victor de Ponte, 05-38087
 */
int main (int argc, char **argv) {
  ///Tiempo en segundos entre cada verificación. Valor por defecto: 30s
  int t;
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
  if (dir_especificado) {
    directorios = (char **) xmalloc(1*sizeof(char*));
    directorios[0] = aVerificar;
  } else {
    ListaStr *dirs = leerArchivo(aVerificar);
    n = dirs->size;
    directorios = LSToArray(dirs);
    LSLiberar(dirs);
    free(dirs);
  }

  pids = (pid_t *) xmalloc(n * sizeof(pid_t));

  signal(SIGCHLD, childHandler); // se instala el nuevo manejador para SIGCHLD

  printf("Bienvenido al monitor de directorios remotos!\n");
  ayuda_cli();
  printf("\n");
  register int i;
  for (i = 0; i < n; i++) {
    char* intervalo = xmalloc(sizeof(char*));
    sprintf(intervalo, "%d", t);
    if ((pids[i]=fork())==0) {
      execl("./verificador", "./verificador", directorios[i], intervalo, NULL);
    }
  }

  char key;
  while (TRUE) {
    key = getChar();
    switch(key)
      {
      case 'h':
        ayuda_cli();
        break;
      case 's':
        printf("Instrucción recibida: STOP\n");
        mens_despedida();
        matarHijos();
        sleep(2);
        exit(0);
        break;
      case 'c':
        printf("Instrucción recibida: CONTINUE\n");
        continuarHijos();
        mens_continuar();
        break;
      case 'p':
        printf("Instrucción recibida: PAUSE\n");
        pausarHijos();
        mens_pausado();
        break;
      default:
        printf("Instrucción desconocida recibida: %c\n",key);
      }
  }

  free(directorios);
  return 0;
}
