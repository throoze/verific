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
LIBS =
OBJS = verific.o

CFLAGS = -w
#CFLAGS =

all: ${EXEC}

${EXEC}: ${OBJS}
	gcc ${CFLAGS} ${OBJS} -o ${EXEC}

verific.o: verific.c verific.h ${LIBS}
	gcc ${CFLAGS} -c verific.c

check-syntax:
	cc -o nul -Wall -S ${CHK_SOURCES}