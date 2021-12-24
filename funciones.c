#include "funciones.h"


//[1]Suma
int suma()
{
    int i;
    int *coef;
    int grado1, grado2, max_grad, aux;

    system("CLS");

    printf("Ingrese el grado del primer polinomio: ");
    scanf("%i", &grado1);

    printf("Ingrese el grado del segundo polinomio: ");
    scanf("%i", &grado2);

    if(grado1 > grado2)
    {
        max_grad = grado1;
    }
    else
    {
        max_grad = grado2;
    }

    /* inicializar arreglo  */
    coef = (int*)malloc(max_grad* sizeof(int));

	 /* llenar arreglo con 0, para evitar errores */
    for(i = 0; i < max_grad; i++)
    {
        coef[i] = 0;
    }

    printf("\n\n----------------------------\n");
    printf("PRIMER POLINOMIO\n");
    printf("\n");

    for(i = 0; i <= grado1; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &coef[i]);
    }

    printf("\n\n----------------------------\n");
    printf("SEGUNDO POLINOMIO\n");
    printf("\n");

    for(i = 0; i <= grado2 ; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &aux);
        coef[i] = coef[i] + aux;
    }

    printf("\n\n----------------------------\n");
    printf("RESULTADO\n");
    printf("----------------------------\n");

    for(i = max_grad; i >= 0; --i)
    {
        if(i == 0)
        {
            printf("%d",  coef[i]);
        }
        else if(i == 1)
        {
            printf("%dx + ",  coef[i]);
        }
        else
        {
            printf("%dx^%i + ", coef[i], i);
        }
    }

    return 0;
    }

//[2]Resta
int resta()
{
    int i;
    int *coef;
    int grado1, grado2, max_grad, aux;

    system("CLS");

    printf("Ingrese el grado del primer polinomio: ");
    scanf("%i", &grado1);

    printf("Ingrese el grado del segundo polinomio: ");
    scanf("%i", &grado2);

    if(grado1 > grado2)
    {
        max_grad = grado1;
    }
    else
    {
        max_grad = grado2;
    }

    /* ---------------------------------- */
    coef = (int*)malloc(max_grad* sizeof(int));

    /* ---------------------------------- */

    for(i = 0; i < max_grad; i++)
    {
        coef[i] = 0;
    }

    printf("\n\n----------------------------\n");
    printf("PRIMER POLINOMIO\n");
    printf("----------------------------\n");

    for(i = 0; i <= grado1; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &coef[i]);
    }

    printf("\n\n----------------------------\n");
    printf("SEGUNDO POLINOMIO\n");
    printf("----------------------------\n");

    for(i = 0; i <= grado2 ; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &aux);
        coef[i] = coef[i] - aux;
    }

    printf("\n\n----------------------------\n");
    printf("RESULTADO\n");
    printf("----------------------------\n");

    for(i = max_grad; i >= 0; --i)
    {
        if(i == 0)
        {
            printf("%d",  coef[i]);
        }
        else if(i == 1)
        {
            printf("%dx + ",  coef[i]);
        }
        else
        {
            printf("%dx^%i + ", coef[i], i);
        }
    }

    return 0;
    }
//[3]Multiplicacion de polinomios
int multiplicacion()
{
    int i,j;
    int *coef, *coef2, *polinomioResultante;
    int grado1, grado2, max;

    system("CLS");

    printf("Ingrese el grado del primer polinomio: ");
    scanf("%i", &grado1);

    printf("Ingrese el grado del segundo polinomio: ");
    scanf("%i", &grado2);

    coef = (int*)malloc(grado1* sizeof(int));
    coef2 = (int*)malloc(grado2* sizeof(int));


    for(i = 0; i <= grado1; i++)
    {
        coef[i] = 0;

    }

    for(i = 0; i <= grado2; i++)
    {
         coef2[i] = 0;
    }

	//Polinomio donde max es un x^(grado1 + grado2)

	max= grado1 + grado2 ;
	polinomioResultante = (int*)malloc(max* sizeof(int));


	//Iniciamos como 0 los valores del polinomio resultante
	for(i = 0; i <= max; i++)
    {
        polinomioResultante[i] = 0;
    }

    printf("\n\n----------------------------\n");
    printf("PRIMER POLINOMIO\n");
    printf("----------------------------\n");

    for(i = 0; i <= grado1; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &coef[i]);
    }

    printf("\n\n----------------------------\n");
    printf("SEGUNDO POLINOMIO\n");
    printf("----------------------------\n");

    for(i = 0; i <= grado2 ; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &coef2[i]);
    }

	//Por cada termino del polinomio1
	for (i = 0; i <= grado1 ; i++){
    //Vamos a multiplicar cada termino del polinomio2
		for (j = 0; j <= grado2 ; j++){
		polinomioResultante[j+i] += coef[i] * coef2[j];
    }
		}

	printf("\n\n----------------------------\n");
    printf("RESULTADO\n");
    printf("----------------------------\n");

    for(j = max; j >= 0; --j)
    {
        if(j == 0)
        {
            printf("%d",  polinomioResultante[j]);
        }
        else if(j == 1)
        {
            printf("%dx + ",  polinomioResultante[j]);
        }
        else
        {
            printf("%dx^%i + ", polinomioResultante[j], j);
        }
    }
}

//[4]Multiplicacion por un Escalar
int escalar()
{
	int i;
	int *coef;
    int grado1, max_grad, aux;

    system("CLS");

    printf("Ingrese el grado del polinomio: ");
    scanf("%i", &grado1);

    printf("Ingrese el escalar: ");
    scanf("%i", &aux);

    /* inicializar arreglo  */
    coef = (int*)malloc(max_grad*sizeof(int));

	 /* llenar arreglo con 0, para evitar errores */
    for(i = 0; i < grado1; i++)
    {
        coef[i] = 0;
    }

    printf("\n\n----------------------------\n");
    printf(" POLINOMIO\n");
    printf("\n");

    for(i = 0; i <= grado1; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &coef[i]);
    }

    printf("\n\n----------------------------\n");


    for(i = 0; i <= grado1 ; i++)
    {
        coef[i] = coef[i] * aux;
    }

    printf("\n\n----------------------------\n");
    printf("RESULTADO\n");
    printf("----------------------------\n");

    for(i = grado1; i >= 0; --i)
    {
        if(i == 0)
        {
            printf("%d",  coef[i]);
        }
        else if(i == 1)
        {
            printf("%dx + ",  coef[i]);
        }
        else
        {
            printf("%dx^%i + ", coef[i], i);
        }
    }

    return 0;

}

//[5]Division entre binomio
int division_binomio()
{
	int i,j;
	int *coef, *coef2, *polinomioResultante;;
    int grado1, grado2=1, max, aux, res;

    system("CLS");

    printf("Ingrese el grado del primer polinomio: ");
    scanf("%i", &grado1);


    coef = (int*)malloc(grado1* sizeof(int));
    coef2 = (int*)malloc(grado2* sizeof(int));



    for(i = 0; i <= grado1; i++)
    {
        coef[i] = 0;

    }

    for(i = 0; i <= grado2; i++)
    {
         coef2[i] = 0;
    }

	//Polinomio resultante donde max es un x^(grado1 - 1)

	max= grado1 - 1;
	polinomioResultante = (int*)malloc(max* sizeof(int));

	//Iniciamos como 0 los valores del polinomio resultante
	for(i = 0; i <= max; i++)
    {
        polinomioResultante[i] = 0;
    }

    printf("\n\n----------------------------\n");
    printf("PRIMER POLINOMIO\n");
    printf("----------------------------\n");

    for(i = 0; i <= grado1; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &coef[i]);
    }

    printf("\n\n----------------------------\n");
    printf("BINOMIO\n");
    printf("----------------------------\n");

    for(i = 0; i <= grado2 ; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &coef2[i]);
    }

	if (coef2[0] > 0){
		aux = coef2[0] * (-1);
	}
	else if (coef2[0] < 0)
    {
        aux = coef2[0];
    }
    printf("----------------------------\n");
    polinomioResultante[max] = coef[grado1];
    /*printf("aux = %d: ", aux);
    printf("\n");
    printf("polinomioResultante[max] = %d: ", polinomioResultante[max]);*/

	//Por cada termino del polinomio1
	for(j = max-1; j >= 0; --j){

		polinomioResultante[j] = (polinomioResultante[j+1] * aux) + coef[j+1] ;
		}
		printf("\n");

		res = (polinomioResultante[0] * aux) + coef[0] ;

	printf("\n\n----------------------------\n");
    printf("RESULTADO\n");
    printf("----------------------------\n");
    printf("El cociente es: \n");

    for(j = max; j >= 0; --j)
    {
        if(j == 0)
        {
            printf("%d",  polinomioResultante[j]);
        }
        else if(j == 1)
        {
            printf("%dx + ",  polinomioResultante[j]);
        }
        else
        {
            printf("%dx^%i + ", polinomioResultante[j], j);
        }
    }
    printf("\nEl residuo es: %d  ", res);
}

//[6]Division entre monomio
int division_monomio()
{
	int i;
	int *coef;
    int grado1, aux;

    system("CLS");

    printf("Ingrese el grado del polinomio: ");
    scanf("%i", &grado1);

    printf("Ingrese el grado del monomio: ");
    scanf("%i", &aux);

    /* inicializar arreglo  */
    coef = (int*)malloc(grado1* sizeof(int));

	 /* llenar arreglo con 0, para evitar errores */
    for(i = 0; i < grado1; i++)
    {
        coef[i] = 0;
    }

    printf("\n\n----------------------------\n");
    printf(" POLINOMIO\n");
    printf("\n");
    printf("NOTA: todos los coeficientes del polinomio deben ser >=1 para evitar indeterminacion por la division entre 0\n\n");

    for(i = 0; i <= grado1; i++)
    {
        printf("Valor del coeficiente grado %i: ", i);
        scanf("%d", &coef[i]);
    }

    printf("\n\n----------------------------\n");


    printf("\n\n----------------------------\n");
    printf("RESULTADO\n");
    printf("----------------------------\n");

    for(i = grado1; i >= 0; --i)
    {
        if(i == 0)
        {
            printf("%d/x^%d", coef[i], aux);
        }
        else if(i == 1)
        {
            printf("x^%d + ",  coef[i]-aux);
        }
        else
        {
            printf("%dx^%i + ", coef[i], i-aux);
        }
    }

    return 0;

}


int opcion(int opc)
{
    switch (opc)
    {
        case 1:
        suma();
        break;
        case 2:
        resta();
        break;
        case 3:
    	multiplicacion();
        break;
        case 4:
        escalar();
        break;
        case 5:
        division_binomio();
        break;
        case 6:
        division_monomio();
        break;
        case 7:
        polinomio_teclado();
        break;
        case 8:
        polinomio_archivo();
        break;
        case 9:
        burbuja();
        break;
        default:
        printf("OPCION INCORRECTA[!]");
    }
    return 0;
}
