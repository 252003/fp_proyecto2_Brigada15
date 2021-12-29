#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__

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
//[9]Ordenar elementos por el metodo de burbuja
int burbuja();

int opcion(int opc);

#endif
