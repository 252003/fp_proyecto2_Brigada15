#include <stdio.h >
#include <stdlib.h >
#include<string.h>
#include "funciones.h"


int opc;

void menu()
{
  printf("Operaciones con polinomios \n");
  printf("[1]Suma \n");
  printf("[2]Resta\n");
  printf("[3]Multiplicacion \n");
  printf("[4]Multiplicacion por un Escalar\n");
  printf("[5]Division entre binomio\n");
  printf("[6]Division entre monomio\n");
  printf("[7]leer polinomio(s) del teclado, imprimirlo(s) y guardarlo(s) en un archivo\n");
  printf("[8]leer polinomio(s) de un archivo e imprimirlo\n");
  printf("[9]Ordenar elementos por el metodo de burbuja\n");


  printf("Selecciona Una Opcion:\n>");
  scanf("%d",&opc);
}

//llenar memoria
int** llenar(int grado, int num) {
	int i,j;
	int **m;
	m = (int **)malloc(grado*sizeof(int*));
	//int **m = new int*[grado];
	for ( i = 0; i < grado; i++) {
        m[i] = (int*)malloc(num*sizeof(int));
//		m[i] = new int[num];
		for ( j = 0; j <= num; j++) {
			printf("Valor del coeficiente grado %i del polinomio %i: ", j, i+1);
        	scanf("%d", &m[i][j]);
			//m[i][j] = 0;
		}
	}
	return m;
	free(m);//liberar memoria
}

//guardar en archivo
void guardar(char *fileName, int **m, int grado, int num){

	int i,j;

	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}
	char linea[80];
	//sprintf(linea, "%d %d\n", filas, cols);
	fputs(linea, fp);
	for (i = 0; i < grado; i++) {
		linea[0] = '\0';
		for (j = 0; j <= num; j++) {

			if(j == 0)
        	{
        	char buffer[50];
			sprintf(buffer, "%d \t", m[i][j]);
			strcat(linea, buffer);
        	}
        	else if(j == 1)
        	{
            char buffer[50];
			sprintf(buffer, "%dx\t", m[i][j]);
			strcat(linea, buffer);
        	}
        	else
        	{
            char buffer[50];
			sprintf(buffer, "%dx^%i\t", m[i][j],j);
			strcat(linea, buffer);

        	}

		}
		int len = strlen(linea);
		linea[len - 1] = '\n';
		fputs(linea, fp);
	}
	fclose(fp);


}

//imprimir polinomios
void imprimir(int **m, int grado, int num) {

	int i,j;

    for (i = 0; i < grado; i++) {
		for (j = 0; j <= num; j++) {

		if(j == 0)
        {
        	printf("%d\t", m[i][j]);
        }
        else if(j == 1)
        {
            printf("%dx\t", m[i][j]);
        }
        else
        {
            printf("%dx^%i\t", m[i][j],j);
        }


		}
		printf("\n");
	}
}

//leer polinomios de un archivo
int** leer(char *fileName, int grado, int num) {

	int i,j;
	int **m;

	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}
	char linea[80];
	fgets(linea, 79, fp);
	char *token = strtok(linea, " ");//10 6
	grado = atoi(token);
	token = strtok(NULL, " ");
	num = atoi(token);
	m = (int **)malloc(grado*sizeof(int*));
//	int **m = new int*[grado];
	for (i = 0; i < grado; i++) {
	    m[i] = (int*)malloc(num*sizeof(int));
//		m[i] = new int[num];
		fgets(linea,79, fp);
		token = strtok(linea, " ");
		m[i][0] = atoi(token);
		for (j = 1; j <= num; j++) {
			token = strtok(NULL, " ");
			m[i][j] = atoi(token);
		}
	}
	fclose(fp);
	return m;


}

//[7]leer polinomio del teclado
int polinomio_teclado()
{
	//int i,j;
    int grado, num;

    system("CLS");

    printf("Ingrese el numero de polinomios a guardar : ");
    scanf("%i", &grado );

    printf("Ingrese el mayor grado del polinomio a guardar : ");
    scanf("%i", &num);


    int **M = llenar(grado, num);
    imprimir(M, grado, num);
    guardar("Polinomios.txt", M, grado, num);


    return 0;
    free(M);//liberar memoria

}

//[8]leer polinomio de un archivo
int polinomio_archivo()
{
	//int i;
    int grado, num;

    system("CLS");

    printf("Ingrese el numero de polinomios a leer : ");
    scanf("%i", &grado );

    printf("Ingrese el mayor grado del polinomio a leer : ");
    scanf("%i", &num);

    printf("NOTA: El archivo a leer solo debe contener los coeficientes de los polinomios \n");

    int **M2 = leer("Poli.txt", grado , num);
	printf("Polinomios en el archivo: \n");
	imprimir(M2, grado, num);


    return 0;
    free(M2);//liberar memoria
}



//MAIN

int main()
{
    menu();
    opcion(opc);
    return 0;

}
