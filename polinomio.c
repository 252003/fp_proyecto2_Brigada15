#include "polinomio.h”
char *pol_cdn;
//ARCHIVOS
void open_in_file(char *filename){
    infile = fopen(filename,"r");
    if(!infile){
        printf("No tienes permisos suficientes para abrir %s\n", filename);
    }
}
void open_out_file(char *filename){
    outfile = fopen(filename, "w");
    if(!outfile){
        printf("No tienes permisos para abrir %s\n", filename);
    }
}
void close_file(FILE *f){
    fclose(f);
}
//AUXILIARES
/**
 * @brief Calcula la potencia
 *
 * @param base
 * @param expo
 * @return int El valor de la potencia
 */
int pot(int base, int expo)
{
    int res = 1;
    for (int i = 0; i < expo; i++)
    {
        res = res * base;
    }
    return res;
}
/**
 * @brief Comvierte una cadena
 *
 * @param str Cadena a convertir
 */
int strtoi(char *str)
{
    int res = 0;
    int num;
    int exp = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++)
    {
        num = ((int)str[i] - 48) * pot(10, exp - i);
        res += num;
    }
    return res;
}
 
/**
 * @brief Copia de una cadena
 *
 * @param str Cadena fuente
 * @param a (a,b] Rango
 * @param b
 * @return char*  sub cadena
 */
char *strcpyrng(char *str, int a, int b)
{
    if (b - a == 0)
    {
        char *ret = (char *)malloc(sizeof(char));
        ret[0] = '1';
        return ret;
    }
    char *ret = (char *)malloc((b - 1 - a) * sizeof(char));
    for (int i = 0; i < b - a; i++)
    {
        ret[i] = str[a + 1 + i];
    }
    ret[b - a] = '\0';
    return ret;
}
/**
 * @brief Busca un carracter en cualquier cadena
 *
 * @param a Cadena en la que buscar
 * @param b El caracter a buscar
 */
bool find(char *a, char b)
{
    int o = strlen(a);
    bool flag = false;
    for (int i = 0; i < o; i++)
    {
        if (a[i] == b)
        {
            flag = true;
            return flag;
        }
    }
    return flag;
}
/**
 * @brief Busca un caracter en un arrgleo
 *
 * @param str El arreglo en que buscar
 * @param c El caracter a buscar
 * @return El indice en el que encuentra el primer caracter
 */
int findstrc(char *str, char c)
{
    int pos = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == c)
        {
            return i;
        }
        pos++;
    }
    return pos;
}
void menu()
{
    printf("----------CALCULADORA DE POLINOMIOS------------\n");
    printf("Opciones\n");
    printf("1.Suma\n");
    printf("2.Resta\n");
    printf("3.Multiplicacion por un escalar\n");
    printf("4.Multiplicacion\n");
    printf("5.Division\n");
    printf("6.Imprimir memoria\n");
    printf("7.Leer polinomio de teclado\n");
    printf("8.Leer polinomio de archivo\n");
    printf("9.Escribir polinomio\n");
    printf("10.");
    printf("11.\n");
    printf("12.Salir\n");
}
void init()
{
    memoria.polis = initmemory();
    memoria.cont = 0;
}
/**
 * @brief Aplica el teorema del resiudo
 *
 * @param Polinomio que se va a evaluar
 * @param x Valor a evaluar
 * @return double
 */
//OPERACIONES
double residuo(POL A, double x)
{
    double r;
    for (int i = 0; i < A.nter; i++)
    {
        r = r + (A.ter[i].coef * pot(x, A.ter[i].exp));
    }
    return r;
}
/**
Suma polinomios
 */
POL add(POL A, POL B)
{
    POL C;
    float aux;
    float exp;
    //INIDICES
    int i = 0;
    int j = 0;
    int k = 0;
    //VALORES
    bool flag = true;
    if (A.ter[0].exp >= B.ter[0].exp)
    {
        C.ter = (TERMINO *)malloc((A.ter[0].exp + 1) * sizeof(TERMINO));
        C.nter = A.ter[0].exp + 1;
    }
    else
    {
        C.ter = (TERMINO *)malloc((B.ter[0].exp + 1) * sizeof(TERMINO));
        C.nter = B.ter[0].exp + 1;
    }
    //SUMA
    for (k = 0; k < C.nter; k++)
    {
        if (A.ter[i].exp == B.ter[j].exp)
        {
            aux = (A.ter[i].exp + B.ter[j].exp);
            if (aux != 0.0f){
                C.ter[k].coef = A.ter[i].coef + B.ter[j].coef;
                C.ter[k].exp = A.ter[i].exp;
            }else{
                k--;
            }
            i++;
            j++;
            /*printf("a\n");*/
        }
        else if (A.ter[i].exp > B.ter[j].exp)
        {
            C.ter[k] = A.ter[i];
            i++;
            /*printf("b\n");*/
        }
        else
        {
            C.ter[k] = B.ter[j];
            j++;
            /*printf("c\n");*/
        }
    }
    int cont = 0;
    i = C.nter - 1;
    while (C.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    C.ter = (TERMINO *)realloc(C.ter, (C.nter - cont) * sizeof(TERMINO));
    C.nter = C.nter - cont;
    return C;
}
 
/**
 * @brief Resta de polinomio
 */
POL sub(POL A, POL B)
{
    POL C;
    //INIDICES
    int i = 0;
    int j = 0;
    int k = 0;
    //VALORES
    bool flag = true;
    //PROCESO
    if (A.ter[0].exp >= B.ter[0].exp)
    {
        C.ter = (TERMINO *)malloc((A.ter[0].exp + 1) * sizeof(TERMINO));
        C.nter = A.ter[0].exp + 1;
    }
    else
    {
        C.ter = (TERMINO *)malloc((B.ter[0].exp + 1) * sizeof(TERMINO));
        C.nter = B.ter[0].exp + 1;
    }
    //RESTA
    for (k = 0; k < C.nter; k++)
    {
        if (A.ter[i].exp == B.ter[j].exp)
        {
            C.ter[k].coef = A.ter[i].coef - B.ter[j].coef;
            C.ter[k].exp = A.ter[i].exp;
            i++;
            j++;
            /* printf("a\n"); */
        }
        else if (A.ter[i].exp > B.ter[j].exp)
        {
            C.ter[k] = A.ter[i];
            i++;
            /*printf("b\n");*/
        }
        else
        {
            C.ter[k].coef = (-1) * B.ter[j].coef;
            C.ter[k].exp = B.ter[j].exp;
            j++;
            /* printf("c\n"); */
        }
    }
    int cont = 0;
    i = C.nter - 1;
    while (C.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    C.ter = (TERMINO *)realloc(C.ter, (C.nter - cont) * sizeof(TERMINO));
    C.nter = C.nter - cont;
    return C;
}
/**
 * @brief Multiplicacion por escalar
 */
POL esc_pol(POL A, double s)
{
    POL C;
    C.ter = (TERMINO *)malloc(A.nter * sizeof(TERMINO));
    C.nter = A.nter;
    for (int i = 0; i < C.nter; i++)
    {
        C.ter[i].coef = A.ter[i].coef * s;
    }
    return C;
}
/**
 * @brief Producto de pólinomios
 */
POL pol_prod(POL A, POL B)
{
    POL C;
    TERMINO tauxi;
    C.ter = (TERMINO *)malloc((A.ter[0].exp + B.ter[0].exp + 1) * sizeof(TERMINO));
    C.nter = A.ter[0].exp + B.ter[0].exp + 1;
    C.ter[0].exp = A.ter[0].exp + B.ter[0].exp;
    for (int i = 0; i < A.nter; i++)
    {
        for (int j = 0; j < B.nter; j++)
        {
            tauxi.coef = A.ter[i].coef * B.ter[j].coef;
            tauxi.exp = A.ter[i].exp + B.ter[j].exp;
            for (int k = 0; k < C.nter; k++)
            {
                if (tauxi.exp == C.ter[k].exp)
                {
                    C.ter[k].coef = C.ter[k].coef + tauxi.coef;
                    C.ter[k].exp = tauxi.exp;
                    break;
                }
                else if (C.ter[k + 1].coef == 0.0)
                {
                    C.ter[k + 1] = tauxi;
                    break;
                }
            }
        }
    }
    int cont = 0;
    int i = C.nter - 1;
    while (C.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    C.ter = (TERMINO *)realloc(C.ter, (C.nter - cont) * sizeof(TERMINO));
    C.nter = C.nter - cont;
    bubble_pol(C);
    return C;
}
/**
 * @brief Division
 */
POL pol_div(POL P, POL Q)
{
    POL C;
    POL ax;
    double res = residuo(P, (-1) * Q.ter[1].coef);
    C.ter = (TERMINO *)malloc((P.grd - Q.grd + 1) * sizeof(TERMINO));
    C.nter = P.grd - Q.grd + 1;
    int j = 1;
    float f = (-1) * Q.ter[1].coef / Q.ter[0].coef;
    int rnulas = P.ter[P.nter - 1].exp;
    ax = polcpy(P);
    pol_print(ax);
    C.ter[0].coef = P.ter[0].coef;
    C.ter[0].exp = P.ter[0].exp - 1;
    for (int i = 1; i < C.nter; i++)
    {
        C.ter[i].coef = ax.ter[i].coef + (f * C.ter[i - 1].coef);
        C.ter[i].exp = ax.ter[i].exp - 1;
    }
    free(ax.ter);
    int cont = 0;
    int i = C.nter - 1;
    while (C.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    C.ter = (TERMINO *)realloc(C.ter, (C.nter - cont) * sizeof(TERMINO));
    C.nter = C.nter - cont;
    bubble_pol(C);
    return C;
}
/**
 * @brief Copia un polinomio A y le baja el grado en 1 y llena de ceros
 *
 * @param A 4x^4
 * @return POL 4x^3 +0x^3 0x^2 0x 0
 */
POL polcpy(POL A)
{
    POL C;
    C.ter = (TERMINO *)malloc((A.grd + 1) * sizeof(TERMINO));
    C.nter = A.grd + 1;
    int j = 0;
    for (int i = 0; i < C.nter; i++)
    {
        C.ter[i].exp = C.nter - i - 1;
    }
    for (int i = 0; i < C.nter; i++)
    {
        if (C.ter[i].exp == A.ter[j].exp)
        {
            C.ter[i].coef = A.ter[j].coef;
            j++;
        }
    }
    C.grd = C.nter - 1;
    return C;
}
/*
 * @brief Metodo de ordenamiento por burbuja
 */
void bubble_sort(int a[], int n)
{
    bool follow = true;
    int pasada, j;
    int limite = n, aux;
    for (int pasada = 0; pasada < limite && follow; pasada++)
    {
        follow = false;
        for (j = 0; j < limite - 1 - pasada; j++)
        {
            if (a[j] < a[j + 1])
            {
                aux = a[j];
                a[j] = a[j + 1];
                a[j + 1] = aux;
                follow = true;
            }
        }
    }
}
 
/**
 * @brief Crea un polinomio con una cantida de terminos igual a nterl y lee
 *
 * @param nterl El numero de terminos
 * @return POL La direccion de memoria para la estructura POL con ntel terminos
 */
POL pol_creat(int nterl)
{
    //<-----VARIABLES------>
    POL A;
    A.ter = (TERMINO *)malloc(nterl * sizeof(TERMINO));
    char c = '1';
    char *pol_aux = (char *)malloc(sizeof(char));
    char *termi = (char *)malloc(sizeof(char));
    char *coef = (char *)malloc(sizeof(char));
    char *exp = (char *)malloc(sizeof(char));
    A.nter = nterl;
    //<-----INDICES----->
    int i = 0;
    int j;
    printf("Introduzca su polinomio: ");
    fflush(stdin);
    while (c != '\n')
    {
        setbuf(stdin, NULL);
        c = getc(stdin);
        if (c == '\n')
        {
            pol_aux = realloc(pol_aux, (i + 1) * sizeof(char));
            pol_aux[i + 1] = '\0';
            break;
        }
        pol_aux = (char *)realloc(pol_aux, (i + 2) * sizeof(char));
        pol_aux[i] = c;
        pol_aux[i + 1] = '\0';
        i++;
    } // a ya tiene mi cadena
    i = 0;
    j = 0;
    for (; i < nterl; i++, pol_aux = NULL)
    {
        termi = strtok(pol_aux, " ");
        /*printf("%s\n", termi);*/
        if (termi != NULL)
        {
            if (find(termi, 'x'))
            {
                if (strlen(termi) == 1) // x
                {
                    A.ter[j].coef = 1;
                    A.ter[j].exp = 1;
                }
                else if (strlen(termi) == 2) //-x //2x
                {
                    if (termi[0] == '-')
                    {
                        A.ter[j].coef = -1;
                        A.ter[j].exp = 1;
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        A.ter[j].coef = strtof(coef, NULL);
                        A.ter[j].exp = 1;
                    }
                }
                else if (strlen(termi) == 3) // x^2    --    //22x  --- -2x
                {
                    if (find(termi, '^'))
                    {
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        /* printf("Exponente %s\n", exp); */
                        A.ter[j].exp = strtoi(exp);
                        A.ter[j].coef = 1;
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        A.ter[j].coef = strtof(coef, NULL);
                        A.ter[j].exp = 1;
                    }
                }
                else if (strlen(termi) == 4) //-x^3 --- x^23 -22x 222x
                {
                    if (termi[0] == '-' && termi[1] == 'x')
                    {
                        A.ter[j].coef = -1;
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        /* printf("Exponente %s\n", exp); */
                        A.ter[j].exp = strtoi(exp);
                    }
                    else if (termi[0] == 'x')
                    {
                        A.ter[j].coef = 1;
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        /* printf("Exponente %s\n", exp); */
                        A.ter[j].exp = strtoi(exp);
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        A.ter[j].coef = strtof(coef, NULL);
                        /* printf("Coeficiente %s\n", coef); */
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        /* printf("Exponente %s\n", exp); */
                        A.ter[j].exp = strtoi(exp);
                    }
                }
                else if (strlen(termi) >= 5)
                {
                    strncpy(coef, termi, findstrc(termi, 'x'));
                    A.ter[j].coef = strtof(coef, NULL);
                    exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                    /* printf("Exponente %s\n", exp); */
                    A.ter[j].exp = strtoi(exp);
                }
            }
            else
            {
                A.ter[j].coef = strtof(termi, NULL);
                A.ter[j].exp = 0;
            }
        }
        j++;
        if (termi == NULL)
            break;
    }
    free(pol_aux);
    bubble_pol(A);
    A.grd = A.ter[0].exp;
    return A;
}
/**
 * @brief Elimina el arreglo de terminos que esta dentro de la estructura POL
 *
 * @param A Polinomio al que borra los terminos
 */
void pol_del(POL A)
{
    free(A.ter);
}
/**
 * @brief Creacion de la memoria
 *
 * @return POL*
 */
POL *initmemory()
{
    POL *d;
    d = (POL *)malloc(10 * sizeof(POL));
    return d;
}
void cpyinmem(POL A)
{
    if (memoria.cont < 10)
    {
        memoria.polis[memoria.cont] = A;
        memoria.cont++;
    }
    else
    {
        memoria.polis = (POL *)realloc(memoria.polis, (memoria.cont + 1) * sizeof(POL));
        memoria.cont++;
    }
}
void printMemory(mem a)
{
    printf("Memoria\n");
    for (int i = 0; i < a.cont; i++)
    {
        printf("%d) ", i + 1);
        pol_print(a.polis[i]);
    }
}
POL recoMemory(mem a, int h)
{
    POL C;
    C.ter = (TERMINO *)malloc(a.polis[h - 1].nter * sizeof(TERMINO));
    C.nter = a.polis[h - 1].nter;
    for (int i = 0; i < C.nter; i++)
    {
        C.ter[i] = a.polis[h - 1].ter[i];
    }
    C.grd = a.polis[h - 1].grd;
    return C;
}
//ESCRITURA
/**
 * @brief Imprime un polinomio A
 */
void pol_print(POL A)
{
    for (int i = 0; i < A.nter; i++)
    {
        printf("%.4fx^%d  ", A.ter[i].coef, A.ter[i].exp);
    }
    printf("\n");
}
//ORDENAMIENTO
/**
 * @brief Implementacion del metodo de ordenamiento por burbuja
 *
 * @param A Polinomio a ordenar de manera decreciente sus exponentes
 */
void bubble_pol(POL A)
{
    bool follow = true;
    int pasada, j;
    TERMINO aux;
    for (int pasada = 0; pasada < A.nter && follow; pasada++)
    {
        follow = false;
        for (j = 0; j < A.nter - 1 - pasada; j++)
        {
            if (A.ter[j].exp < A.ter[j + 1].exp)
            {
                aux = A.ter[j];
                A.ter[j] = A.ter[j + 1];
                A.ter[j + 1] = aux;
                follow = true;
            }
        }
    }
}
POL fpol_creat(char *pol_aux)
{
    //VARIABLES
    POL A;
    A.nter=0;
    char c = '1';
    char *termi = (char *)malloc(sizeof(char));
    char *coef = (char *)malloc(sizeof(char));
    char *exp = (char *)malloc(sizeof(char));
    //INDICES
    int i = 0;
    int j;
    fflush(stdin);
    i = 0;
    j = 0;
    for (;;pol_aux = NULL)
    {
        termi = strtok(pol_aux, " ");
        A.nter++;
        /*printf("%s\n", termi);*/
        A.ter=(TERMINO*)realloc(A.ter,A.nter*sizeof(TERMINO));
        if (termi != NULL)
        {
            if (find(termi, 'x'))
            {
                if (strlen(termi) == 1)
                {
                    A.ter[j].coef = 1;
                    A.ter[j].exp = 1;
                }
                else if (strlen(termi) == 2)
                {
                    if (termi[0] == '-')
                    {
                        A.ter[j].coef = -1;
                        A.ter[j].exp = 1;
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        A.ter[j].coef = strtof(coef, NULL);
                        A.ter[j].exp = 1;
                    }
                }
                else if (strlen(termi) == 3)
                {
                    if (find(termi, '^'))
                    {
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        A.ter[j].exp = strtoi(exp);
                        A.ter[j].coef = 1;
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        A.ter[j].coef = strtof(coef, NULL);
                        A.ter[j].exp = 1;
                    }
                }
                else if (strlen(termi) == 4)
                {
                    if (termi[0] == '-' && termi[1] == 'x')
                    {
                        A.ter[j].coef = -1;
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        /* printf("Exponente %s\n", exp); */
                        A.ter[j].exp = strtoi(exp);
                    }
                    else if (termi[0] == 'x')
                    {
                        A.ter[j].coef = 1;
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        /* printf("Exponente %s\n", exp); */
                        A.ter[j].exp = strtoi(exp);
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        A.ter[j].coef = strtof(coef, NULL);
                        /* printf("Coeficiente %s\n", coef); */
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        /* printf("Exponente %s\n", exp); */
                        A.ter[j].exp = strtoi(exp);
                    }
                }
                else if (strlen(termi) >= 5)
                {
                    strncpy(coef, termi, findstrc(termi, 'x'));
                    A.ter[j].coef = strtof(coef, NULL);
                    exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                    /* printf("Exponente %s\n", exp); */
                    A.ter[j].exp = strtoi(exp);
                }
            }
            else
            {
                A.ter[j].coef = strtof(termi, NULL);
                A.ter[j].exp = 0;
            }
        }
        j++;
        if (termi == NULL) break;
    }
    free(pol_aux);
    bubble_pol(A);
    A.grd = A.ter[0].exp;
    return A;
}
