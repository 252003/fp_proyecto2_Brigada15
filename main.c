#include "polinomio.h"

int main(int argc, char **argv)
{
    if (argc == 7)
    {
        if (strcmp(argv[1], "-in") == 0)
        {
            open_in_file(argv[2]);
        }
        else if (strcmp(argv[1], "-out") == 0)
        {
            open_out_file(argv[2]);
        }
        else if (strcmp(argv[1], "-re") == 0)
        {
            open_registro(argv[2]);
        }
        if (strcmp(argv[3], "-in") == 0)
        {
            open_in_file(argv[4]);
        }
        else if (strcmp(argv[3], "-out") == 0)
        {
            open_out_file(argv[4]);
        }
        else if (strcmp(argv[3], "-re") == 0)
        {
            open_registro(argv[4]);
        }
        if (strcmp(argv[5], "-in") == 0)
        {
            open_in_file(argv[6]);
        }
        else if (strcmp(argv[5], "-out") == 0)
        {
            open_out_file(argv[6]);
        }
        else if (strcmp(argv[5], "-re") == 0)
        {
            open_registro(argv[6]);
        }
    }
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
        else if (strcmp(argv[1], "-re") == 0)
        {
            open_registro(argv[2]);
        }
        if (strcmp(argv[3], "-in") == 0)
        {
            open_in_file(argv[4]);
        }
        else if (strcmp(argv[3], "-out") == 0)
        {
            open_out_file(argv[4]);
        }
        else if (strcmp(argv[3], "-re") == 0)
        {
            open_registro(argv[4]);
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
        else if (strcmp(argv[1], "-re") == 0)
        {
            open_registro(argv[2]);
        }
    }
    POL X, Y, Z;
    DIV D;
    int t, t1;
    int op;
    float l;
    char *polZ;
    init();
    while (op != 12)
    {
        system("clear");
        menu();
        printf("¿Qué desea realizar?\n");
        scanf("%d", &op);
        if (op < 1 || op > 10)
        {
            printf("Opción incorrecta, introduzca de nuevo\n");
            scanf("%d", &op);
        }
        switch (op)
        {
        case 1:
            printf("Suma\n");
            cdnprint();
            printf("Selecione 2 de acuerdo al numero y separados por un tabulador\n");
            scanf("%d\t%d", &t, &t1);
            X = recoMemory(memoria, t);
            Y = recoMemory(memoria, t1);
            Z = add(X, Y);
            polZ = POLtoSTR(Z);
            cpy_in_almacen(polZ);
            cpyinmem(Z);
            break;
        case 2:
            printf("Resta\n");
            cdnprint();
            printf("Selecione 2 de acuerdo al numero y separados por un tabulador\n");
            scanf("%d\t%d", &t, &t1);
            X = recoMemory(memoria, t);
            Y = recoMemory(memoria, t1);
            Z = sub(X, Y);
            polZ = POLtoSTR(Z);
            cpy_in_almacen(polZ);
            cpyinmem(Z);
            break;
        case 3:
            printf("Multiplicacion por escalar\n");
            cdnprint();
            printf("Selecione 1 deacuerdo al numero y un escalar separados por un tabulador\n");
            scanf("%d\t%f", &t, &l);
            X = recoMemory(memoria, t);
            Z = esc_pol(X, l);
            polZ = POLtoSTR(Z);
            cpy_in_almacen(polZ);
            cpyinmem(Z);
            break;
        case 4:
            printf("Multiplicación\n");
            cdnprint();
            printf("Selecione 2 deacuerdo al numero y separelos por un tabulador\n");
            scanf("%d\t%d", &t, &t1);
            X = recoMemory(memoria, t);
            Y = recoMemory(memoria, t1);
            Z = pol_prod(X, Y);
            polZ = POLtoSTR(Z);
            cpy_in_almacen(polZ);
            cpyinmem(Z);
            break;
        case 5:
            printf("Division\n");
            cdnprint();
            printf("Selecione 2 deacuerdo al numero y separelos por un tabulador\n");
            scanf("%d\t%d", &t, &t1);
            X = recoMemory(memoria, t);
            Y = recoMemory(memoria, t1);
            D = div_larga(X, Y);
            polZ = POLtoSTR(D.cociente);
            cpy_in_almacen(polZ);
            polZ = POLtoSTR(D.residuo);
            cpy_in_almacen(polZ);
            cpyinmem(D.cociente);
            cpyinmem(D.residuo);
            break;
        case 6:
            if (memoria.cont == 0)
            {
                printf("No hay nada en la memoria");
            }
            else
            { 
                cdnprint();
            }
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
            Z = fread_pol(infile);
            cpyinmem(Z);
            break;
        case 9:
            printf("Escriba polinomio en archivo\n");
            cdnprint();
            printf("Seleciona tu polinomio: ");
            scanf("%d", &t);
            fwrite_pol(t);
            break;
        case 10:
            printf("Salir\n");
            if (argc == 7)
            {
                if (strcmp(argv[1], "-in") == 0)
                {
                    fclose(infile);
                }
                else if (strcmp(argv[1], "-out") == 0)
                {
                    fclose(outfile);
                }
                else if (strcmp(argv[1], "-re") == 0)
                {
                    fclose(registro);
                }
                if (strcmp(argv[3], "-in") == 0)
                {
                    fclose(infile);
                }
                else if (strcmp(argv[3], "-out") == 0)
                {
                    fclose(outfile);
                }
                else if (strcmp(argv[3], "-re") == 0)
                {
                    fclose(registro);
                }
                if (strcmp(argv[5], "-in") == 0)
                {
                    fclose(infile);
                }
                else if (strcmp(argv[5], "-out") == 0)
                {
                    fclose(outfile);
                }
                else if (strcmp(argv[5], "-re") == 0)
                {
                    fclose(registro);
                }
            }
            else if (argc == 5)
            {
                if (strcmp(argv[1], "-in") == 0)
                {
                    fclose(infile);
                }
                else if (strcmp(argv[1], "-out") == 0)
                {
                    fclose(outfile);
                }
                else if (strcmp(argv[1], "-re") == 0)
                {
                    fclose(registro);
                }
                if (strcmp(argv[3], "-in") == 0)
                {
                    fclose(infile);
                }
                else if (strcmp(argv[3], "-out") == 0)
                {
                    fclose(outfile);
                }
                else if (strcmp(argv[3], "-re") == 0)
                {
                    fclose(registro);
                }
            }
            else if (argc == 3)
            {
                if (strcmp(argv[1], "-in") == 0)
                {
                    fclose(infile);
                }
                else if (strcmp(argv[1], "-out") == 0)
                {
                    fclose(outfile);
                }
                else if (strcmp(argv[1], "-re") == 0)
                {
                    fclose(registro);
                }
                exit(0);
                break;
            }
        }
    }
    return 0;
}
