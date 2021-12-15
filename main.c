#include "polinomio.h"
// ./a,out -in entrada.txt -out salida.txt
int main(int argc, char **argv)
{
    if (argc == 5)
    { // ya que están separadas por espacios
        if (strcmp(argv[1], "-in") == 0)
        { // si es igual regresa 0
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
    //Declaracion de Variables
    POL A, B, C;
    int t;
    int op;
    int l;
    char c[2];
    c[1] = '\0';
    char *str = (char *)malloc(sizeof(char));//Memoria Dinamica
    c[0] = fgetc(infile);
    while (c[0] != '\n')
    {
        strcat(str, c);
        c[0] = fgetc(infile);
    }
    A = fpol_creat(str);
    pol_print(A);
    init();
    while (op != 12)
    {
        system("clear");
        menu();
        printf("¿Qué desea realizar?\n");
        scanf("%d", &op);
        //Creamos un Switch, para que el usuario interactue con el programa
        switch (op)
        {
        case 1:
            printf("Suma\n");
            printf("Ingrese el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            A = pol_creat(t);
            printf("Ingrese el numero de terminos para su segundo polinomio\n");
            scanf("%d", &l);
            B = pol_creat(t);
            C = add(A, B);
            cpyinmem(C);
            printMemory(memoria);
            getc(stdin);
            break;
        case 2:
            printf("Resta\n");
            printf("Ingrese el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            A = pol_creat(t);
            printf("Ingrese el numero de terminos para su segundo polinomio\n");
            scanf("%d", &l);
            B = pol_creat(t);
            C = sub(A, B);
            cpyinmem(C);
            printMemory(memoria);
            getc(stdin);
            break;
        case 3:
            printf("Multiplicacion por escalar\n");
            printf("Ingrese el polinomio\n");
            scanf("%d", &t);
            A = pol_creat(t);
            printf("Ingrese el escalar\n");
            scanf("%d", &l);
            C = esc_pol(A, l);
            cpyinmem(C);
            printMemory(memoria);
            getc(stdin);
            break;
        case 4:
            printf("Multiplicación\n");
            printf("Ingrese el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            A = pol_creat(t);
            printf("Ingrese el numero de terminos para su segundo polinomio\n");
            scanf("%d", &l);
            B = pol_creat(t);
            C = pol_prod(A, B);
            cpyinmem(C);
            printMemory(memoria);
            getc(stdin);
            break;
        case 5:
            printf("Division\n");
            printf("Ingrese el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            A = pol_creat(t);
            printf("Ingrese el numero de terminos para su segundo polinomio\n");
            scanf("%d", &l);
            B = pol_creat(t);
            C = pol_div(A, B);
            cpyinmem(C);
            printMemory(memoria);
            getc(stdin);
            break;
        case 6:
            printf("Division entre un polinomio y un monomio\n");
            printf("Ingrese el numero de terminos para su primer polinomio\n");
            scanf("%d", &t);
            A = pol_creat(t);
            printf("Ingrese el numero de terminos para su segundo polinomio\n");
            scanf("%d", &l);
            B = pol_creat(t);
            C = pol_div(A, B);
            cpyinmem(C);
            printMemory(memoria);
            getc(stdin);
            break;
        case 7:
            printf("Leer polinomio de teclado\n");
            printf("Cuantos terminos tiene?\n");
            scanf("%d", &t);
            A = pol_creat(t);
            pol_print(A);
            cpyinmem(A);
            break;
        case 8:
            printf("8.Leer polinomio de archivo\n");
            c[0] = fgetc(infile);
            while (c[0] != '\n')
            {
                strcat(str, c);
                c[0] = fgetc(infile);
            }
            A = fpol_creat(str);
            break;
        case 9:
            free(memoria.polis);
            free(A.ter);
            free(B.ter);
            exit(0);
            break;
        }
    }
    return 0;
}
 
