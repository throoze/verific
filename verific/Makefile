################################################################################
#                                                                              #
# PROYECTO 1: Aplicacion para la verificación de cambios en directorios        #
#                                                                              #
# Archivo: Makefile                                                            #
# Descripción: Archivo encargado de garantizar la compilación correcta y en    #
#              orden, óptima, cuidando las dependencias entre librerías.       #
#                                                                              #
# Universidad Nacional Experimental Simón Bolívar                              #
# Departamento de Computación y Tecnología de la Información                   #
# Redes de computadoras 1                                                      #
# Trimestre Septiembre - Diciembre 2011                                        #
# Profesores: Ricardo Gonzales, Carlos Gómez                                   #
# @author Jerilyn Goncalves, 05-38242                                          #
# @author Victor de Ponte, 05-38087                                            #
# @version 1.0                                                                 #
################################################################################

EXEC = verific
LIBS = almacenamiento.h expreg.h util.h
OBJS = almacenamiento.o expreg.o util.o

#CFLAGS = -w
CFLAGS =
MAINFLAGS =
EXECS = verific verificador

all: ${EXECS}

verificador: verificador.o ${OBJS}
	gcc ${CFLAGS} verificador.o ${OBJS} ${MAINFLAGS} -o verificador

verific: verific.o ${OBJS}
	gcc ${CFLAGS} verific.o ${OBJS} ${MAINFLAGS} -o verific

verificador.o: verificador.c verificador.h ${LIBS}
	gcc ${CFLAGS} -c verificador.c

verific.o: verific.c verific.h ${LIBS}
	gcc ${CFLAGS} -c verific.c

almacenamiento.o: almacenamiento.c almacenamiento.h
	gcc ${CFLAGS} -c almacenamiento.c

expreg.o: expreg.c expreg.h
	gcc ${CFLAGS} -c expreg.c

util.o: util.c util.h
	gcc ${CFLAGS} -c util.c

check-syntax:
	cc -o nul -Wall -S ${CHK_SOURCES}