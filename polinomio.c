#include "polinomio.h"

//----ARCHIVOS----
/**
 * @brief abre el archivo
 *
 * @param filename el nombre de nuestro archivo 
 */
void open_in_file(char *filename)
{
    infile = fopen(filename, "r");
    if (!infile)
    {
        printf("No tienes permisos para abrir %s\n", filename);
    }
}
/**
 * @brief abre el archivo de salida
 *
 * @param filename el nombre del archivo de salida
 */
void open_out_file(char *filename)
{
    outfile = fopen(filename, "w");
    if (!outfile)
    {
        printf("No tienes permisos para abrir %s\n", filename);
    }
}
/**
 * @brief Abre el archivo de nuestro registro
 *
 * @param filename El nombre del achivo registro
 */
void open_registro(char *filename)
{
    registro = fopen(filename, "w");
    if (!registro)
    {
        printf("No tiene permisos para abrir el archivo\n");
    }
}
/**
 * @brief Cierra el archivo
 *
 * @param f El archvo que va a cerrar
 */
void close_file(FILE *f)
{
    fclose(f);
}
/**
 * @brief Lee un polinomio de un archivo
 *
 * @param in El archivo entrada
 * @return POL El polinomio obtenido
 */
POL fread_pol(FILE *in)
{
    POL X;
    X.ter = (TERMINO *)malloc(sizeof(TERMINO));
    X.nter = 0;
    int j = 0;
    char *termi = (char *)malloc(sizeof(char));
    char *coef = (char *)malloc(sizeof(char));
    char *exp = (char *)malloc(sizeof(char));
    char *pol = NULL;
    size_t numbytes=0;
    getline(&pol, &numbytes, in);
    cpy_in_almacen(pol);
    for (;; pol = NULL)
    {
        termi = strtok(pol, " ");
        /*printf("%s\n", termi);*/
        if (termi != NULL)
        {
            X.ter = (TERMINO *)realloc(X.ter, (X.nter + 1) * sizeof(TERMINO));
            X.nter++;
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
                        X.ter[j].exp = 1;
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
        if (termi == NULL)
            break;
    }
    free(coef);
    free(exp);
    free(pol);
    bubble_pol(X);
    return X;
}
/**
 * @brief Escribe en un archivo
 *
 * @param i La poscion del polinomio 
 */
void fwrite_pol(int i)
{
    fputs(almacen.cdn[i - 1], outfile);
}
//----AUXILIARES----
/**
 * @brief Calcula la potencia 
 *
 * @param base
 * @param expo
 * @return int el valor de la potencia
 */
int pot(int base, int expo)
{
    int residuo = 1;
    for (int i = 0; i < expo; i++)
    {
        residuo = residuo * base;
    }
    return residuo;
}
/**
 * @brief Convierte una cadena 
 * @param str Cadena a convertir
 */
int strtoi(char *str)
{
    int res = 0;
    int n;
    int exp = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++)
    {
        n = ((int)str[i] - 48) * pot(10, exp - i);
        res += n;
    }
    return res;
}

/**
 * @brief Copia de una cadena 
 *
 * @param str Cadena fuente
 * @param x rango
 * @param y
 * @return char* sub cadena
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
 * @brief Busca un caracater
 *
 * @param x Cadena a buscar
 * @param y El caracter a buscar
 * @return true (verdadero)
 * @return false (falso)
 */
bool find(char *x, char y)
{
    int c = strlen(x);
    bool f = false;
    for (int i = 0; i < c; i++)
    {
        if (x[i] == y)
        {
            f = true;
            return f;
        }
    }
    return f;
}
/**
 * @brief Busca un caracter en un arrgleo
 *
 * @param str El arreglo a buscar
 * @param d El caracter a buscar
 * @return int El indice que se va a encontrar
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
    printf("----------BIENVENID@S A LA CALCULADORA DE POLINOMIOS------------\n");
    printf("Opciones\n");
    printf("1.Suma\n");
    printf("2.Resta\n");
    printf("3.Multiplicacion por un escalar\n");
    printf("4.Multiplicacion\n");
    printf("5.Division\n");
    printf("6.Imprimir memoria\n");
    printf("7.Leer polinomio desde teclado\n");
    printf("8.Leer polinomio desde archivo\n");
    printf("9.Escribir polinomio en un archivo\n");
    printf("10.Salir\n");
}
void init()
{
    memoria.polis = initmemory();
    memoria.cont = 0;
    almacen.cdn = (char **)malloc(10 * sizeof(char *));
    almacen.cont = 0;
}
/**
 * @brief Resuelve una ecuacion de grado lineal
 *
 * @return double El valor de a
 */
double lineal(double x, double y, double z)
{
    double a;
    a = (z - y) / x;
    return a;
}

/**
 * @brief Crea un polinomio 
 *
 * @param nterl el numero de terminos
 * @return POL la direccion de memoria 
 */
POL pol_creat(int nterl)
{
    POL X;
    X.ter = (TERMINO *)malloc(nterl * sizeof(TERMINO));
    char c = '1';
    char *pol_aux = (char *)malloc(sizeof(char));
    char *termi = (char *)malloc(sizeof(char));
    char *coef = (char *)malloc(sizeof(char));
    char *exp = (char *)malloc(sizeof(char));
    X.nter = nterl;
    int i = 0;
    int j;
    printf("Escriba su polinomio: ");
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
    }
    cpy_in_almacen(pol_aux);
    i = 0;
    j = 0;
    for (; i < nterl; i++, pol_aux = NULL)
    {
        termi = strtok(pol_aux, " ");
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
                        X.ter[j].exp = 1;
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
        if (termi == NULL)
            break;
    }
    bubble_pol(X);
    X.grd = X.ter[0].exp;
    return X;
}

/**
 * @brief Implementacion del metodo de ordenamiento por burbuja
 * @param X Polinomio a ordenar de manera decreciente 
 */
void bubble_pol(POL X)
{
    bool follow = true;
    int pasada;
    int j;
    TERMINO aux;
    for (pasada = 0; pasada < X.nter && follow; pasada++)
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

//----OPERACIONES----
/**
 * @brief Elimina los ceros de un polinomio 
 * @param X Polinomio a eliminar
 * @return POL
 */
POL pol_cero(POL X)
{
    POL D;
    D = cpy(X);
    int cont = 0;
    int pas = 0; 
    TERMINO aux;
    bool flag = true;
    int i = 0;
    while (flag)
    {
        i = 0;
        flag = false;
        pas++;
        while (i < D.nter - pas)
        {
            if (D.ter[i].coef == 0.0f)
            {
                flag = true;
                aux = D.ter[i];
                D.ter[i] = D.ter[i + 1];
                D.ter[i + 1] = aux;
            }
            i++;
        }
    }
    if (D.ter[0].coef == 0.0f)
    {
        D.ter = (TERMINO *)realloc(D.ter, (sizeof(TERMINO)));
        D.nter = 1;
        D.ter[0].coef = 0;
        D.ter[0].exp = 0;
        return D;
    }
    i = D.nter - 1;
    while (D.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    D.ter = (TERMINO *)realloc(D.ter, (D.nter - cont) * (sizeof(TERMINO)));
    D.nter = D.nter - cont;
    bubble_pol(D);
    return D;
}
/**
 * @brief Suma de polinomios
 *
 * @param X
 * @param Y
 * @return POL el resultado de la variable C
 */
POL add(POL X, POL Y)
{
    POL Z;
    int i = 0;
    int j = 0;
    int k = 0;
    //----VALORES----
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
            Z.ter[k].coef = X.ter[i].coef + Y.ter[j].coef;
            Z.ter[k].exp = X.ter[i].exp;
            i++;
            j++;
        }
        else if (X.ter[i].exp > Y.ter[j].exp)
        {
            Z.ter[k] = X.ter[i];
            i++;
        }
        else if (X.ter[i].exp < Y.ter[j].exp)
        {
            Z.ter[k].coef = Y.ter[j].coef;
            Z.ter[k].exp = Y.ter[j].exp;
            j++;
        }
        if (j == Y.nter && i == X.nter)
            break;
    }
    Z = pol_cero(Z);
    return Z;
}

/**
 * @brief Resta de polinomios
 * @param X
 * @param Y
 * @return POL
 */
POL sub(POL X, POL Y)
{
    POL Z;
    int i = 0;
    int j = 0;
    int k = 0;
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
    for (k = 0; k < Z.nter; k++)
    {
        if (X.ter[i].exp == Y.ter[j].exp)
        {
            Z.ter[k].coef = X.ter[i].coef - Y.ter[j].coef;
            Z.ter[k].exp = X.ter[i].exp;
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
            Z.ter[k].coef = (-1) * Y.ter[j].coef;
            Z.ter[k].exp = Y.ter[j].exp;
            j++;
        }
        if (j == Y.nter && i == X.nter)
            break;
    }
    Z = pol_cero(Z);
    return Z;
}

/**
 * @brief Producto de polinomios 
 * @param A
 * @param B
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
    Z=pol_cero(Z);
    return Z;
}

/**
 * @brief Multiplicacion por escalar
 *
 * @param A polinomio
 * @param m escalar
 * @return POL
 */
POL esc_pol(POL X, double m)
{
    POL Z;
    Z.ter = (TERMINO *)malloc(X.nter * sizeof(TERMINO));
    Z.nter = X.nter;
    for (int i = 0; i < Z.nter; i++)
    {
        Z.ter[i].coef = X.ter[i].coef * m;
        Z.ter[i].exp = X.ter[i].exp;
    }
    return Z;
}

/**
 * @brief Division P/Q
 *
 * @param E
 * @param D
 * @return POL
 */
POL pol_div(POL E, POL D)
{
    POL Z;
    POL ax;
    Z.ter = (TERMINO *)malloc((E.grd - D.grd + 1) * sizeof(TERMINO));
    Z.nter = E.grd - D.grd + 1;
    float f = (-1) * D.ter[1].coef / D.ter[0].coef;
    ax = polcpy(E);
    pol_print(ax);
    Z.ter[0].coef = E.ter[0].coef;
    Z.ter[0].exp = E.ter[0].exp - 1;
    for (int i = 1; i < Z.nter; i++)
    {
        Z.ter[i].coef = ax.ter[i].coef + (f * Z.ter[i - 1].coef);
        Z.ter[i].exp = ax.ter[i].exp - 1;
    }
    free(ax.ter);
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
DIV div_larga(POL X, POL Y)
{
    DIV Z;
    Z.cociente.ter = (TERMINO *)malloc(sizeof(TERMINO));
    Z.cociente.nter = 0;
    POL auxi;
    auxi = cpy(X);
    POL auxi2;
    POL mono;
    mono.ter = (TERMINO *)malloc(sizeof(TERMINO));
    mono.nter = 1;
    while (auxi.ter[0].exp >= Y.ter[0].exp)
    {
        mono.ter[0].coef = auxi.ter[0].coef / Y.ter[0].coef;
        mono.ter[0].exp = auxi.ter[0].exp - Y.ter[0].exp;
        
        Z.cociente.ter = (TERMINO *)realloc(Z.cociente.ter, (Z.cociente.nter + 1) * sizeof(TERMINO));
        Z.cociente.ter[Z.cociente.nter] = mono.ter[0];
        pol_print(Z.cociente);
        Z.cociente.nter++;
        auxi2 = pol_prod(mono, Y);
        pol_print(auxi2);
        auxi = sub(auxi, auxi2);
    }
    Z.residuo = auxi;
    return Z;
}
/**
 * @brief Copia un polinomio
 * @param A 
 * @return POL 
 */
POL polcpy(POL X)
{
    POL Z;
    Z.ter = (TERMINO *)malloc((X.grd + 1) * sizeof(TERMINO));
    Z.nter = X.grd + 1;
    int j = 0;
    for (int i = 0; i < Z.nter; i++)
    {
        Z.ter[i].exp = Z.nter - i - 1;
    }
    for (int i = 0; i < Z.nter; i++)
    {
        if (Z.ter[i].exp == X.ter[j].exp)
        {
            Z.ter[i].coef = X.ter[j].coef;
            j++;
        }
    }
    Z.grd = Z.nter - 1;
    return Z;
}
POL cpy(POL X)
{
    POL Y;
    Y.ter = (TERMINO *)malloc(X.nter * sizeof(TERMINO));
    for (int i = 0; i < X.nter; i++)
    {
        Y.ter[i] = X.ter[i];
    }
    Y.nter = X.nter;
    return Y;
}
TERMINO esp_ter(char *str){
    TERMINO x;
        if (strcmp(str,"x"))
        {
            x.coef=1;
            x.exp=1;
            return x;
        }else if (strcmp(str,"-x"))
        {
            x.coef=-1;
            x.exp=1;
            return x;
        }
    return x;
}
TERMINO t_read(char *str){
    TERMINO x;
    char *coef;
        if (find(str,'x'))
        {
            
        }
        else
        {
            x.coef=strtof(str,NULL);
        }
    return x;
}

/**
 * @brief Elimina el arreglo de terminos que esta dentro de la estructura POL
 *
 * @param X Polinomio al que borra los terminos
 */
void pol_del(POL X)
{
    free(X.ter);
}
/**
 * @brief Creacion de la memoria
 *
 * @return POL*
 */
POL *initmemory()
{
    POL *c;
    c = (POL *)malloc(10 * sizeof(POL));
    return c;
}
void cpyinmem(POL X)
{
    if (memoria.cont < 10)
    {
        memoria.polis[memoria.cont] = X;
        memoria.cont++;
    }
    else
    {
        memoria.polis = (POL *)realloc(memoria.polis, (memoria.cont + 1) * sizeof(POL));
        memoria.polis[memoria.cont] = X;
        memoria.cont++;
    }
}
void cpy_in_almacen(char *c)
{
    if (almacen.cont < 10)
    {
        almacen.cdn[almacen.cont] = (char *)malloc(sizeof(char));
        strcpy(almacen.cdn[almacen.cont], c);
        almacen.cont++;
    }
    else
    {
        almacen.cdn = (char **)realloc(almacen.cdn, (almacen.cont + 1) * (sizeof(char *)));
        almacen.cdn[almacen.cont] = (char *)malloc(sizeof(char));
        strcpy(almacen.cdn[almacen.cont], c);
        almacen.cont++;
    }
}
/**
 * @brief Imprime la memoria hasta el momento
 *
 * @param a La memoria que vamos a imprimir
 */
void printMemory(mem x)
{
    printf("Memoria\n");
    for (int i = 0; i < x.cont; i++)
    {
        printf("%d) ", i + 1);
        pol_print(x.polis[i]);
    }
}
/**
 * @param a La memoria a la que se va a acceder
 * @param h La posicion en la que esta dicho polinomio
 * @return POL El polinomio recuperado
 */
POL recoMemory(mem x, int g)
{
    POL Z;
    Z.ter = (TERMINO *)malloc(x.polis[g - 1].nter * sizeof(TERMINO));
    Z.nter = x.polis[g - 1].nter;
    for (int i = 0; i < Z.nter; i++)
    {
        Z.ter[i] = x.polis[g - 1].ter[i];
    }
    Z.grd = x.polis[g - 1].grd;
    return Z;
}
void cdnprint()
{
    for (int i = 0; i < almacen.cont; i++)
    {
        printf("%d)", i + 1);
        for (int j = 0; j < strlen(almacen.cdn[i]); j++)
        {
            printf("%c", almacen.cdn[i][j]);
        }
        printf("\n");
    }
}
char *POLtoSTR(POL X)
{
    char *ter = (char *)malloc(sizeof(char));
    char *pol = (char *)malloc(sizeof(char));
    for (int i = 0; i < X.nter; i++)
    {
        if (X.ter[i].exp == 0)
        {
            sprintf(ter, "%.4f", X.ter[i].coef);
            strcat(pol, ter);
        }
        else
        {

            sprintf(ter, "%.4fx^%d", X.ter[i].coef, X.ter[i].exp);
            strcat(pol, ter);
        }
        if (i < X.nter - 1)
        {
            strcat(pol, " ");
        }
    }
    free(ter);
    return pol;
}

/**
 * @brief imprime el polinomio 
 * @param X
 */
void pol_print(POL X)
{
    for (int i = 0; i < X.nter; i++)
    {
        printf("%.4fx^%d  ", X.ter[i].coef, X.ter[i].exp);
    }
    printf("\n");
}

