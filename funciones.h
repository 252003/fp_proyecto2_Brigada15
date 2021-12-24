#ifndef FUNCIONESH
#define FUNCIONESH

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int opc, grado, num;



//[1]Suma
int suma();
//[2]Resta
int resta();
//[3]Multiplicacion de polinomios
int multiplicacion();
//[4]Multiplicacion por un Escalar
int escalar();
//[5]Division entre binomio
int division_binomio();
//[6]Division entre monomio
int division_monomio();
//[7]leer polinomio del teclado
int polinomio_teclado();
//[8]leer polinomio de un archivo
int polinomio_archivo();

int opcion(int opc);

#endif
