#include "matriz/matriz.h"

int main(){
    
    double mtr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    matriz *mtr1 = matriz_crear(3, 3, mtr);
    matriz *mtr2 = matriz_crear(3, 3, mtr);

    matriz *mtr3 = matriz_suma(mtr1, mtr2);

    matriz_consola_imprimir(mtr1);
    matriz_consola_imprimir(mtr2);
    matriz_consola_imprimir(mtr3);

    return 0;

}
