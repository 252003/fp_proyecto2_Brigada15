CC=gcc #Indicamos que el el compilador que se empleará es gcc
CCDEBUG=-g -Wall
CCSTD=-std=c99
CCFLAGS= $(CCSTD) $(CCDEBUG)
LIBS= -lm
FILES= ecuaciones main
CCFILES=$(addsuffix .c, $(FILES))
OBJS=$(addsuffix .o, $(FILES))
 
EXE=solucion
 
.PHONY = all
all: polinomio main polinomio
 
polinomio: polinomio.c
    $(CC) $(CCFLAGS) -c $< -o polinomio.o $(LIBS)
 
main: main.c
    $(CC) $(CCFLAGS) -c $< -o main.o
 
polinomio: polinomio.h
    $(CC) $(CCFLAGS) -c $< -o polinomio.o
