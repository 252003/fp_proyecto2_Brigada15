#ifndef _POLINOMIO_H_
#define _POLINOMIO_H_
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
struct _termino
{
    float coef;
    int exp;
    //char var;
};
typedef struct _termino TERMINO; //Estructura para guardar las partes de un término
struct polinomio
{
    int nter;
    int grd;
   TERMINO *ter;
};
typedef struct polinomio POL;
struct _mpol
{
    int cont;//Aqui se va a guardar el polinomio
    POL *polis;
};
typedef struct _mpol mem;
mem memoria;
 
//ARCHIVOS
FILE *infile;
FILE *outfile;
void open_in_file(char *); //Funciones para abrir un archivo
void open_out_file(char *);
void close_file(FILE *f); //Siempre que abrimos un archivo, debemos cerrarlo
POL fpol_creat(char *);
 
//AUXILIARES
int pot(int base, int expo);
int findstrc(char *str, char c);
int strtoi(char *str);
char *strcpyrng(char *, int a, int b);
bool find(char *, char);
int findstrc(char *str, char c);
void menu();
void init();
 
//OPERACIONES
double residuo(POL, double);
POL add(POL, POL);
POL sub(POL, POL);
POL esc_pol(POL, double);
POL pol_prod(POL, POL);
POL pol_div(POL, POL);
POL polcpy(POL);
void cpyinmem(POL);
 
//MEMORIA
POL pol_creat(int nter);
void pol_del(POL A);
POL *initmemory();
void printMemory(mem);
POL recoMemory(mem, int);
 
//ESCRITURA
void pol_print(POL A);
TERMINO read_ter(char *a);
 
//ORDENAMIENTO
void bubble_sort(int a[], int n); //Utilizaremos el método de ordenamiento por 
void bubble_pol(POL); //burbuja para ordenar los términos del polinomio
#endif
