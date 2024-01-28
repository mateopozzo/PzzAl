#include "../include/matriz.h"
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    matriz *mtr1;
    mtr1 = matriz_consola_cargar();

    matriz_consola_imprimir(mtr1);
    matriz *mtr2 = matriz_triangular(mtr1);
    matriz_consola_imprimir(mtr2);
    float_t det1=0, det2=0;
    matriz_determinante(mtr1, &det1);
    matriz_determinante(mtr2, &det2);
    printf("%f %f\n", det1, det2);
/*
    if( mtr1 == 0 || mtr2 == 0 ){
        printf("Una de las matrices no se pudo cargar\n");
        return 1;
    }

    matriz *mtr3 = matriz_producto_matricial(mtr1, mtr2);

    matriz_consola_imprimir(mtr1);
    matriz_consola_imprimir(mtr2);
    matriz_consola_imprimir(mtr3);

    matriz_eliminar(mtr1);
    matriz_eliminar(mtr2);
    matriz_eliminar(mtr3);
  */  
    return 0;
}
