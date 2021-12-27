CC=gcc #Indica que el compilador que se emplea es gcc
CCDEBUG=-g -Wall
CCSTD=-std=c99
CCFLAGS= $(CCSTD) $(CCDEBUG)
LIBS= -lm
FILES= funciones main
CCFILES=$(addsuffix .c, $(FILES))
OBJS=$(addsuffix .o, $(FILES))
 
EXE=solucion
 
.PHONY = all
all: funciones main 
 
funciones: funciones.c
    $(CC) $(CCFLAGS) -c $< -o polinomio.o $(LIBS)
 
main: main.c
    $(CC) $(CCFLAGS) -c $< -o main.o
 
funciones: funciones.h
    $(CC) $(CCFLAGS) -c $< -o polinomio.o
 
