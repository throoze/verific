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
OBJS = verific.o almacenamiento.o expreg.o util.o

CFLAGS = -w
#CFLAGS =

all: ${EXEC}

${EXEC}: ${OBJS}
	gcc ${CFLAGS} ${OBJS} -o ${EXEC}

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