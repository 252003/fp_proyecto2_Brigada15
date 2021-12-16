#include "polinomio.h"
char *pol_cdn;
//-----ARCHIVOS-----
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
//----AUXILIARES----
/**
 * @brief Calcula la potencia 
 *
 * @param base
 * @param expo
 * @return int el valor de la potencia
 */
int pot(int base, int exp)
{
    int res = 1;
    for (int i = 0; i < exp; i++)
    {
        res = res * base;
    }
    return res;
}
/**
 * @brief convierte una cadena que representa un entero 
 *
 * @param str cadena a convertir
 * @return int
 */
int strtoi(char *str)
{
    int res = 0;
    int numero;
    int exp = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++)
    {
        numero = ((int)str[i] - 48) * pot(10, exp - i);
        res += numero;
    }
    return res;
}

/**
 * @brief copia de una cadena 
 *
 * @param str cadena fuente
 * @param x rango
 * @param y
 * @return char* La sub cadena
 */
char *strcpyrng(char *str, int x, int y)
{
    if (y - x == 0)
    {
        char *ret = (char *)malloc(sizeof(char));
        ret[0] = '1';
        return ret;
    }
    char *ret = (char *)malloc((y - 1 - x) * sizeof(char));
    for (int i = 0; i < y - x; i++)
    {
        ret[i] = str[x + 1 + i];
    }
    ret[y - x] = '\0';
    return ret;
}
/**
 * @brief busca un caracter en un a cadena
 *
 * @param a Cadena a buscar
 * @param b El caracter a buscar
 * @return true (verdadero)
 * @return false (falso)
 */
bool find(char *a, char b)
{
    int u = strlen(a);
    bool flag = false;
    for (int i = 0; i < u; i++)
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
 * @brief busca un caracter en un arrgleo
 *
 * @param str el arreglo a buscar
 * @param d el caracter a buscar
 * @return int el indice del primer caracter              
 */
int findstrc(char *str, char d)
{
    int pos = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == d)
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
    printf("6.Imprimir\n");
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
 *
 * @param A polinomio a evaluar
 * @param x el valor a evaluar
 */
//----OPERACIONES----
double residuo(POL A, double x)
{
    double p;
    for (int i = 0; i < A.nter; i++)
    {
        p = p + (A.ter[i].coef * pot(x, A.ter[i].exp));
    }
    return p;
}
/**
 * @brief suma de polinomios 
 *
 * @param X
 * @param Y
 * @return POL resultado
 */
POL add(POL X, POL Y)
{
    POL Z;
    float aux;
    float exp;
    //----INIDICES----
    int i = 0;
    int j = 0;
    int k = 0;
    //----VALORES----
    bool flag = true;
    //----PROCESO----
    if (X.ter[0].exp >= Y.ter[0].exp)
    {
        Z.ter = (TERMINO *)malloc((X.ter[0].exp + 1) * sizeof(TERMINO));
        Z.nter = X.ter[0].exp + 1;
    }
    else
    {
        Z.ter = (TERMINO *)malloc((Y.ter[0].exp + 1) * sizeof(TERMINO));
        Z.nter = Y.ter[0].exp + 1;
    }
    //----SUMA----
    for (k = 0; k < Z.nter; k++)
    {
        if (X.ter[i].exp == Y.ter[j].exp)
        {
            aux = X.ter[i].coef + Y.ter[j].coef;
            if(aux != 0.0f){
                Z.ter[k].coef = X.ter[i].coef + Y.ter[j].coef;
                Z.ter[k].exp = X.ter[i].exp;
            }else{
                k--;
            }
            i++;
            j++;
        }
        else if (X.ter[i].exp > Y.ter[j].exp)
        {
            Z.ter[k] = X.ter[i];
            i++;
        }
        else
        {
            Z.ter[k] = Y.ter[j];
            j++;
        }
    }
    int cont = 0;
    i = Z.nter - 1;
    while (Z.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    Z.ter = (TERMINO *)realloc(Z.ter, (Z.nter - cont) * sizeof(TERMINO));
    Z.nter = Z.nter - cont;
    return Z;
}

/**
 * @brief Resta de polinomio
 * @param A
 * @param B
 * @return POL
 */
POL sub(POL A, POL B)
{
    POL C;
    //----INDICES----
    int l = 0;
    int m = 0;
    int n = 0;
    //----VOLORES----
    bool flag = true;
    //----PROCESO----
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
    //----SUMA----
    for (n = 0; n < C.nter; n++)

    {
        if (A.ter[l].exp == B.ter[m].exp)
        {
            C.ter[n].coef = A.ter[l].coef - B.ter[m].coef;
            C.ter[n].exp = A.ter[l].exp;
            l++;
            m++;
        }
        else if (A.ter[l].exp > B.ter[m].exp)
        {
            C.ter[n] = A.ter[l];
            l++;
        }
        else
        {
            C.ter[n].coef = (-1) * B.ter[m].coef;
            C.ter[n].exp = B.ter[m].exp;
            m++;
        }
    }
    int cont = 0;
    l = C.nter - 1;
    while (C.ter[l].coef == 0.0f)
    {
        cont++;
        l--;
    }
    C.ter = (TERMINO *)realloc(C.ter, (C.nter - cont) * sizeof(TERMINO));
    C.nter = C.nter - cont;
    return C;
}
/**
 * @brief Producto de pólinomios 
 *
 * @param X
 * @param Y
 * @return POL
 */
POL pol_prod(POL X, POL Y)
{
    POL Z;
    TERMINO tauxi;
    Z.ter = (TERMINO *)malloc((X.ter[0].exp + Y.ter[0].exp + 1) * sizeof(TERMINO));
    Z.nter = X.ter[0].exp + Y.ter[0].exp + 1;
    Z.ter[0].exp = X.ter[0].exp + Y.ter[0].exp;
    for (int i = 0; i < X.nter; i++)
    {
        for (int j = 0; j < Y.nter; j++)
        {
            tauxi.coef = X.ter[i].coef * Y.ter[j].coef;
            tauxi.exp = X.ter[i].exp + Y.ter[j].exp;
            for (int k = 0; k < Z.nter; k++)
            {
                if (tauxi.exp == Z.ter[k].exp)
                {
                    Z.ter[k].coef = Z.ter[k].coef + tauxi.coef;
                    Z.ter[k].exp = tauxi.exp;
                    break;
                }
                else if (Z.ter[k + 1].coef == 0.0)
                {
                    Z.ter[k + 1] = tauxi;
                    break;
                }
            }
        }
    }
    int cont = 0;
    int i = Z.nter - 1;
    while (Z.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    Z.ter = (TERMINO *)realloc(Z.ter, (Z.nter - cont) * sizeof(TERMINO));
    Z.nter = Z.nter - cont;
    bubble_pol(Z);
    return Z;
}
/**
 * @brief Multiplicacion por escalar
 *
 * @param D polinomio
 * @param s escalar
 * @return POL
 */
POL esc_pol(POL D, double s)
{
    POL V;
    V.ter = (TERMINO *)malloc(D.nter * sizeof(TERMINO));
    V.nter = D.nter;
    for (int i = 0; i < V.nter; i++)
    {
        V.ter[i].coef = D.ter[i].coef * s;
    }
    return V;
}
/**
 * @brief Division 
 *
 * @param W
 * @param H
 * @return POL
 */
POL pol_div(POL W, POL H)
{
    POL D;
    POL ax;
    double res = residuo(W, (-1) * H.ter[1].coef);
    D.ter = (TERMINO *)malloc((W.grd - H.grd + 1) * sizeof(TERMINO));
    D.nter = W.grd - H.grd + 1;
    int j = 1;
    float f = (-1) * H.ter[1].coef / H.ter[0].coef;
    int rnulas = W.ter[W.nter - 1].exp;
    ax = polcpy(W);
    pol_print(ax);
    D.ter[0].coef = W.ter[0].coef;
    D.ter[0].exp = W.ter[0].exp - 1;
    for (int i = 1; i < D.nter; i++)
    {
        D.ter[i].coef = ax.ter[i].coef + (f * D.ter[i - 1].coef);
        D.ter[i].exp = ax.ter[i].exp - 1;
    }
    free(ax.ter);
    int cont = 0;
    int i = D.nter - 1;
    while (D.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    D.ter = (TERMINO *)realloc(D.ter, (D.nter - cont) * sizeof(TERMINO));
    D.nter = D.nter - cont;
    bubble_pol(D);
    return D;
}
/**
 * @brief copia un polinomio
 *
 * @param A 
 */
POL polcpy(POL A)
{
    POL P;
    P.ter = (TERMINO *)malloc((A.grd + 1) * sizeof(TERMINO));
    P.nter = A.grd + 1;
    int j = 0;
    for (int i = 0; i < P.nter; i++)
    {
        P.ter[i].exp = P.nter - i - 1;
    }
    for (int i = 0; i < P.nter; i++)
    {
        if (P.ter[i].exp == A.ter[j].exp)
        {
            P.ter[i].coef = A.ter[j].coef;
            j++;
        }
    }
    P.grd = P.nter - 1;
    return P;
}
/*
 * @brief ordenamiento por burbuja
 *
 * @param a el arreglo a ordenar
 * @param n el tamaño del arreglo
 */
void bubble_sort(int s[], int m)
{
    bool follow = true;
    int pasada, j;
    int limite = m, aux;
    for (int pasada = 0; pasada < limite && follow; pasada++)
    {
        follow = false;
        for (j = 0; j < limite - 1 - pasada; j++)
        {
            if (s[j] < s[j + 1])
            {
                aux = s[j];
                s[j] = s[j + 1];
                s[j + 1] = aux;
                follow = true;
            }
        }
    }
}

//----ORDENAMIENTO POR BURBUJA----
/**
 * @brief implementamos el metodo de ordenamiento por burbuja 
 * @param A Polinomio a ordenar de manera decreciente sus exponentes
 */
void bubble_pol(POL X)
{
    bool follow = true;
    int pasada, j;
    TERMINO aux;
    for (int pasada = 0; pasada < X.nter && follow; pasada++)
    {
        follow = false;
        for (j = 0; j < X.nter - 1 - pasada; j++)
        {
            if (X.ter[j].exp < X.ter[j + 1].exp)
            {
                aux = X.ter[j];
                X.ter[j] = X.ter[j + 1];
                X.ter[j + 1] = aux;
                follow = true;
            }
        }
    }
}

//----MEMORIA----
/**
 * @brief Crea un polinomio con una cantidad de terminos
 *
 * @param nterl numero de terminos
 * @return POL direccion de memoria 
 */
POL pol_creat(int nterl)
{
    //----VARIABLES----
    POL A;
    A.ter = (TERMINO *)malloc(nterl * sizeof(TERMINO));
    char c = '1';
    char *pol_aux = (char *)malloc(sizeof(char));
    char *termi = (char *)malloc(sizeof(char));
    char *coef = (char *)malloc(sizeof(char));
    char *exp = (char *)malloc(sizeof(char));
    A.nter = nterl;
    //----INDICES----
    int k = 0;
    int j;
    printf("Escriba su polinomio: ");
    fflush(stdin);
    while (c != '\n')
    {
        setbuf(stdin, NULL);
        c = getc(stdin);
        if (c == '\n')
        {
            pol_aux = realloc(pol_aux, (k + 1) * sizeof(char));
            pol_aux[k + 1] = '\0';
            break;
        }
        pol_aux = (char *)realloc(pol_aux, (k + 2) * sizeof(char));
        pol_aux[k] = c;
        pol_aux[k + 1] = '\0';
        k++;
    } 
    k = 0;
    j = 0;
    for (; k < nterl; k++, pol_aux = NULL)
    {
        termi = strtok(pol_aux, " ");
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
                        A.ter[j].exp = strtoi(exp);
                    }
                    else if (termi[0] == 'x')
                    {
                        A.ter[j].coef = 1;
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        A.ter[j].exp = strtoi(exp);
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        A.ter[j].coef = strtof(coef, NULL);
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        A.ter[j].exp = strtoi(exp);
                    }
                }
                else if (strlen(termi) >= 5)
                {
                    strncpy(coef, termi, findstrc(termi, 'x'));
                    A.ter[j].coef = strtof(coef, NULL);
                    exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
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

//----ESCRITURA----
/**
 * @brief imprime un polinomio 
 *
 * @param A
 */
void pol_print(POL X)
{
    for (int i = 0; i < X.nter; i++)
    {
        printf("%.4fx^%d  ", X.ter[i].coef, X.ter[i].exp);
    }
    printf("\n");
}

POL fpol_creat(char *pol_aux)
{

/**
 * @brief Elimina el arreglo de terminos
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
void cpyinmem(POL C)
{
    if (memoria.cont < 10)
    {
        memoria.polis[memoria.cont] = C;
        memoria.cont++;
    }
    else
    {
        memoria.polis = (POL *)realloc(memoria.polis, (memoria.cont + 1) * sizeof(POL));
        memoria.cont++;
    }
}
void printMemory(mem x)
{
    printf("Memoria\n");
    for (int i = 0; i < x.cont; i++)
    {
        printf("%d) ", i + 1);
        pol_print(x.polis[i]);
    }
}
POL recoMemory(mem x, int h)
{
    POL Z;
    Z.ter = (TERMINO *)malloc(x.polis[h - 1].nter * sizeof(TERMINO));
    Z.nter = x.polis[h - 1].nter;
    for (int i = 0; i < Z.nter; i++)
    {
        Z.ter[i] = x.polis[h - 1].ter[i];
    }
    Z.grd = x.polis[h - 1].grd;
    return Z;
}

    //----VARIABLES----
    POL X;
    X.nter=0;
    char c = '1';
    char *termi = (char *)malloc(sizeof(char));
    char *coef = (char *)malloc(sizeof(char));
    char *exp = (char *)malloc(sizeof(char));

    //----INDICES----
    int m = 0;
    int j;
    fflush(stdin);
    m = 0;
    j = 0;
    for (;;pol_aux = NULL)
    {
        termi = strtok(pol_aux, " ");
        X.nter++;
        X.ter=(TERMINO*)realloc(X.ter,X.nter*sizeof(TERMINO));
        if (termi != NULL)
        {
            if (find(termi, 'x'))
            {
                if (strlen(termi) == 1) 
                {
                    X.ter[j].coef = 1;
                    X.ter[j].exp = 1;
                }
                else if (strlen(termi) == 2) 
                {
                    if (termi[0] == '-')
                    {
                        X.ter[j].coef = -1;
                        X.ter[j].exp = 1;
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        X.ter[j].coef = strtof(coef, NULL);
                        X.ter[j].exp = 0;
                    }
                }
                else if (strlen(termi) == 3) 
                {
                    if (find(termi, '^'))
                    {
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        X.ter[j].exp = strtoi(exp);
                        X.ter[j].coef = 1;
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        X.ter[j].coef = strtof(coef, NULL);
                        X.ter[j].exp = 1;
                    }
                }
                else if (strlen(termi) == 4)
                {
                    if (termi[0] == '-' && termi[1] == 'x')
                    {
                        X.ter[j].coef = -1;
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        X.ter[j].exp = strtoi(exp);
                    }
                    else if (termi[0] == 'x')
                    {
                        X.ter[j].coef = 1;
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        X.ter[j].exp = strtoi(exp);
                    }
                    else
                    {
                        strncpy(coef, termi, findstrc(termi, 'x'));
                        X.ter[j].coef = strtof(coef, NULL);
                        exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                        X.ter[j].exp = strtoi(exp);
                    }
                }
                else if (strlen(termi) >= 5)
                {
                    strncpy(coef, termi, findstrc(termi, 'x'));
                    X.ter[j].coef = strtof(coef, NULL);
                    exp = strcpyrng(termi, findstrc(termi, '^'), strlen(termi));
                    X.ter[j].exp = strtoi(exp);
                }
            }
            else
            {
                X.ter[j].coef = strtof(termi, NULL);
                X.ter[j].exp = 0;
            }
        }
        j++;
        if (termi == NULL) break;
    }
    free(pol_aux);
    bubble_pol(X);
    X.grd = X.ter[0].exp;
    return X;
}
