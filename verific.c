/****************************************************************************
 * PROYECTO 1: Aplicacion para la verificación de cambios en directorios    *
 *                                                                          *
 * verific.c                                                                *
 *                                                                          *
 * @author Jerilyn Goncalves, 05-38242                                      *
 * @author Victor de Ponte, 05-38087                                        *
 * @version 1.0                                                             *
 ****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

/****************************************************************************
 * mensaje_ayuda                                                            *
 *                                                                          *
 * Función que imprime en pantalla un mensaje de ayuda con la sintaxis,     *
 * y la descripción de los parámetros de invocación del programa            *
 ****************************************************************************/
void mensaje_ayuda ()
{

    printf("\nEL PROGRAMA DEBE SER INVOCADO DE LA SIGUIENTE FORMA:\n");
    printf("\tverific  [-t num_segundos] [-d directorio] [-a archivo]\n");
    printf("DONDE:\n");
    printf("\t-t num_segundos: Valor entero que representa el numero de segundos que deben\n");
    printf("\t\t\t transcurrir entre dos revisiones\n");
    printf("\t-d directorio: Especifica el URL del directorio a monitorizar\n");
    printf("\t-a archivo.txt: Archivo que contendrá los URL de los directorios a monitorizar\n");
    printf("\t[ ]: Indica que lo que esté entre esos símbolos es opcional\n");
    printf("\tLA ESPECIFICACION DEL directorio O DEl archivo ES OBLIGATORIA.\n");
    printf("\tEn caso de que la opción -d y -a sean especificadas simultanea-\n");
    printf("\tmente, se verificará solamente el directorio que esta especi-\n");
    printf("\tficado en el parámetro –d. Si el parámetro –t no es especificado,\n");
    printf("\tse puede asumir un valor por defecto de 30 segundos.\n");
}

/****************************************************************************
 * main                                                                     *
 *                                                                          *
 * Programa principal                                                       *
 *                                                                          *
 * Donde:                                                                   *
 *  argc: Número de parametros con el que se hizo la invocación al          *
 *        programa.                                                         *
 *  argv: verific  [-t num_segundos] [-d directorio] [-a archivo]           *
 *        -t num_segundos:  Valor entero que representa el numero de segun_ *
 *                          dos que deben transcurrir entre dos revisiones  *
 *                          consecutivas del directorio(s) a monitorizar.   *
 *                          Por defecto: 30                                 *
 *        -d directorio:    Corresponde a la direccion absoluta de un di_   *
 *                          rectorio (URL) que sera monitorizado            *
 *        -a archivo:       Archivo en formato de texto plano donde cada    *
 *                          linea especifica el URL correspondiente a un    *
 *                          directorio cuya informacion se desea verificar  *
 ****************************************************************************/
int main (int argc, char * argv[])
{

    printf("\nPROYECTO 1: Monitor de cambios en un directorio\n");
    int dir_especificado=0;
    int arch_especificado=0;
    int contador;
    int tipo_entero;
    int num_segundos=30; //Intervalo de tiempo en segundos para la revision.
    char * d="."; //Directorio a analizar.
    char * archivo; //Archivo que contendrá la lista de directorios y archivos encontrados en el directorio.

    //Analiza los parámetros con los que fue invocado el programa:
    if (argc==1) {
            printf("\nNO HA ESPECIFICADO LOS PARAMETROS DEL PROGRAMA\n");
            mensaje_ayuda(); //Llama a la funcion que muestra en pantalla el mensaje de ayuda.
            printf("\nEL PROGRAMA HA TERMINADO\n\n");
            exit(0);
    } else {
        for (contador=1; contador<argc; contador++) {
            //Intervalo de tiempo:
            if (strcmp(argv[contador],"-t")==0){
                //Determina si no se ingreso el intervalo correctamente:
                if((argv[contador+1])==NULL || (sscanf(argv[contador+1],"%d",&tipo_entero)==0)){
                    printf("\n\tFALTO INGRESAR EL INTERVALO DE TIEMPO (num_segundos)\n");
                    mensaje_ayuda(); //Llama a la funcion que muestra en pantalla el mensaje de ayuda.
                    printf("\nEL PROGRAMA HA TERMINADO\n\n");
                    exit(0);
                } else {
                    num_segundos=atoi(argv[contador+1]); //Intervalo de tiempo en segundos para la revision.
                    //printf("\n\tEl intervalo de tiempo en segundos para la revision es: %d\n",num_segundos);
                }
            //Directorio a analizar:
            } else if (strcmp(argv[contador],"-d")==0) {
                d=argv[contador+1];
                //printf("\n\tLa direccion del directorio a analizar es: %s\n",d);
                dir_especificado=1;
            } else if (strcmp(argv[contador],"-a")==0) {
                archivo=argv[contador+1];
                //printf("\n\tEl archivo con la direccion del directorio a analizar es: %s\n", archivo);
                arch_especificado=1;
            } else {
                printf("\nNO HA ESPECIFICADO LOS PARAMETROS DEL PROGRAMA CORRECTAMENTE\n");
                mensaje_ayuda(); //Llama a la funcion que muestra en pantalla el mensaje de ayuda.
                printf("\nEL PROGRAMA HA TERMINADO\n\n");
                exit(0);
            }
            contador++;
        }
    }

    if (dir_especificado==0 && arch_especificado==0) {
        printf("\nNO HA ESPECIFICADO EL DIRECTORIO A MONITORIZAR\n");
        mensaje_ayuda(); //Llama a la funcion que muestra en pantalla el mensaje de ayuda.
        printf("\nEL PROGRAMA HA TERMINADO\n\n");
        exit(0);
    } else {
        printf("\n\tEl intervalo de tiempo en segundos para la revision es: %d\n",num_segundos);
        if (dir_especificado) {
            printf("\n\tLa direccion del directorio a analizar es: %s\n",d);
        } else {
            printf("\n\tEl archivo con la direccion del directorio a analizar es: %s\n", archivo);
        }
        //Llama a la función que se encarga del analisis del directorio:
        printf("\nANALISIS\n");
        printf("\nEL PROGRAMA HA TERMINADO\n\n");
    }
}
