#include "polinomio.h"

int main(int argc, char **argv)
{
    if (argc == 5)
    { 
        if (strcmp(argv[1], "-in") == 0)
        { 
            open_in_file(argv[2]);
        }
        else if (strcmp(argv[1], "-out") == 0)
        {
            open_out_file(argv[2]);
        }
        if (strcmp(argv[3], "-in") == 0)
        {
            open_in_file(argv[4]);
        }
        else if (strcmp(argv[3], "-out") == 0)
        {
            open_out_file(argv[4]);
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-in") == 0)
        {
            open_in_file(argv[2]);
        }
        else if (strcmp(argv[1], "-out") == 0)
        {
            open_out_file(argv[2]);
        }
    }
    POL X, Y, Z;
    int t;
    int op;
    int l;
    char c[2];
    c[1] = '\0';
    char *str = (char *)malloc(sizeof(char));
    c[0] = fgetc(infile);
    while (c[0] != '\n')
    {
        strcat(str, c);
        c[0] = fgetc(infile);
    }
    X = fpol_creat(str);
    pol_print(X);
    init();
    while (op != 12)
    {
        system("clear");
        menu();
        printf("¿Qué  operacion desea realizar?\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("Suma\n");
            printf("Escriba el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            X = pol_creat(t);
            printf("Escriba el numero de terminos para su segundo polinomio\n");
            scanf("%d", &l);
            Y = pol_creat(t);
            Z = add(X, Y);
            cpyinmem(Z);
            printMemory(memoria);
            getc(stdin);
            break;
        case 2:
            printf("Resta\n");
            printf("Escriba el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            X = pol_creat(t);
            printf("Escriba el numero de terminos para su segundo polinomio\n");
            scanf("%d", &t);
            Y = pol_creat(t);
            Z = sub(X, Y);
            cpyinmem(Z);
            printMemory(memoria);
            getc(stdin);
            break;
        case 3:
            printf("Multiplicacion por escalar\n");
            printf("Escriba el polinomio\n");
            scanf("%d", &t);
            X = pol_creat(t);
            printf("Escriba el escalar\n");
            scanf("%d", &l);
            Z = esc_pol(X, l);
            cpyinmem(Z);
            printMemory(memoria);
            getc(stdin);
            break;
        case 4:
            printf("Multiplicación\n");
            printf("Escriba el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            X = pol_creat(t);
            printf("Escriba el numero de terminos para su segundo polinomio\n");
            scanf("%d", &t);
            Y = pol_creat(t);
            Z = pol_prod(X, Y);
            cpyinmem(Z);
            printMemory(memoria);
            getc(stdin);
            break;
        case 5:
            printf("Division\n");
            printf("Escriba el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            X = pol_creat(t);
            printf("Escriba el numero de terminos para su segundo polinomio\n");
            scanf("%d", &t);
            Y = pol_creat(t);
            Z = pol_div(X, Y);
            cpyinmem(Z);
            printMemory(memoria);
            getc(stdin);
            break;
        case 6:
            break;
        case 7:
            printf("Leer polinomio de teclado\n");
            printf("Cuantos terminos tiene?\n");
            scanf("%d", &t);
            X = pol_creat(t);
            pol_print(X);
            cpyinmem(X);
            break;
        case 8:
            printf("8.Leer polinomio de archivo\n");
            c[0] = fgetc(infile);
            while (c[0] != '\n')
            {
                strcat(str, c);
                c[0] = fgetc(infile);
            }
            X = fpol_creat(str);
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            free(memoria.polis);
            free(X.ter);
            free(Y.ter);
            exit(0);
            break;
        }
    }
    return 0;
}
