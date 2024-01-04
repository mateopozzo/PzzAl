#include "../include/matriz.h"
#include <stdio.h>

int main(void){
    
    matriz *mtr1 = matriz_consola_cargar();
    matriz *mtr2 = matriz_consola_cargar();

    if( mtr1 == 0 || mtr2 == 0 ){
        printf("Una de las matrices no se pudo cargar\n");
        return 1;
    }

    matriz *mtr3 = matriz_producto_matricial(mtr1, mtr2);

    matriz_consola_imprimir(mtr1);
    matriz_consola_imprimir(mtr2);
    matriz_consola_imprimir(mtr3);

    return 0;

}
