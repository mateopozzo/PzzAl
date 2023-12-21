#include "../include/matriz.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


matriz*
matriz_crear(size_t col, size_t fl, double_t *arr_val)
{
    //  Devuelve puntero a una nueva matriz

    if( col > MATRIZ_SIZE_MAX || fl > MATRIZ_SIZE_MAX )     return 0;

    matriz *mtr = malloc(sizeof(matriz));

    int tam = col * fl;
    mtr->arr_val = malloc(sizeof(double) * tam);
    mtr->columna = col;
    mtr->fila = fl;

    return mtr;
}


void
matriz_consola_imprimir(matriz *mtr){
    
    if(mtr==NULL)   return;

    for(int i=0; i<mtr->fila; i++){
        for(int j=0; j<mtr->columna; j++)
           printf("%f ", mtr->arr_val[i*mtr->fila+j]);
        printf("\n");
    }

}


matriz*
matriz_suma(matriz *mtr_a, matriz *mtr_b)
{
    //  Devuelve una nueva matriz, suma de los dos argumentos
    
    if( mtr_a->columna != mtr_b->columna || mtr_a->fila != mtr_b->fila )    return 0;

    size_t col = mtr_a->columna, fl = mtr_b->fila;

    double_t *arr_val = malloc(sizeof(double_t) * col * fl);

    for(int i=0; i<col*fl; i++)
        arr_val[i] = mtr_a->arr_val[i] + mtr_b->arr_val[i];

    return matriz_crear(col, fl, arr_val);
}


