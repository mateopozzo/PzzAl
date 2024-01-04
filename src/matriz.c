#include "../include/matriz.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*================================================================================================*/
// Funciones y macros de aplicacion interna
#define DET2X2(a)   *a * *(a+3) - *(a+1) * *(a+2)\

#define SARRUS(a)   a[0] * a[4] * a[8] +\
                    a[1] * a[5] * a[6] +\
                    a[2] * a[3] * a[7] -\
                    (a[2] * a[4] * a[6] +\
                    a[0] * a[5] * a[7] +\
                    a[1] * a[3] * a[8])
/*
double_t
determinante_recursivo(matriz *ptr, size_t col, size_t fl)
{
    return 0;
}


bool
lineas_paralelas(matriz *mtr)
{
    // Paso clave en optimizacion de determinante
    
    double_t *ptr_fila, *ptr_col, *ptr_itr;
    bool flag = false;
    ptr_fila = mtr->array_values;

    while( ptr_fila < mtr->array_values+mtr->fila && !flag ){
        ptr_itr = ptr_fila + mtr->columna;
        ptr_fila++;
    }

    return flag;
}
*/

/*================================================================================================*/


//Funciones visibles de libreria

matriz*
matriz_crear(size_t col, size_t fl, float_t **matriz_valores)
{
    if( col > MATRIZ_SIZE_MAX || fl > MATRIZ_SIZE_MAX )     return 0;

    matriz *mtr = malloc(sizeof(matriz));

    mtr->columna = col;
    mtr->fila = fl;
    mtr->ptr_valores = malloc(sizeof(float_t*) * fl);

    uint8_t i, j;

    for( i=0; i<fl; i++ ){
        mtr->ptr_valores[i] = malloc(sizeof(float_t) * col);
        for( j=0; j<col; j++ ){
            mtr->ptr_valores[i][j] = matriz_valores[i][j];
        }
    }

    return mtr;
}


void
matriz_eliminar(matriz *mtr)
{
    for( uint8_t i=0; i<mtr->fila; ){
       free(mtr->ptr_valores[i]);
       mtr->ptr_valores[i] = NULL;
    }
    free(mtr->ptr_valores);
    mtr->ptr_valores = NULL;
    free(mtr);
}


void
matriz_consola_imprimir(matriz *mtr)
{    
    if(mtr==NULL)   return;

    for(int i=0; i<mtr->fila; i++){
        for(int j=0; j<mtr->columna; j++)
           printf("%f ", mtr->ptr_valores[i][j]);
        printf("\n");
    }

}


matriz *
matriz_consola_cargar(void)
{
    size_t filas, columnas;
    char * aux_in = malloc(sizeof(char) * 100);
    printf("tamaño de la matriz\nfilas: ");
    
    //  lee consola y guarda la fila
    fgets(aux_in, 5, stdin);
    filas = atoi(aux_in);
    if( filas > MATRIZ_SIZE_MAX || filas <= 0 ) return NULL;

    //  lee consola y guarda la columna
    printf("columnas: ");
    fgets(aux_in, 5, stdin);
    columnas = atoi(aux_in);
    if(columnas > MATRIZ_SIZE_MAX ) return NULL;

    float_t **ptr_valores = malloc(sizeof(float_t*) * filas);
    if( ptr_valores == NULL || filas <= 0 ) return NULL;

    for( uint8_t i=0; i<filas; i++ ){
        ptr_valores[i] = malloc(sizeof(float_t) * columnas);
        if( ptr_valores[i] == NULL ) return NULL;

        for( uint8_t j=0; j<columnas; j++ ){
           fgets(aux_in, 100, stdin);
            ptr_valores[i][j] = atoi(aux_in);
        }
    }
    
    return matriz_crear(columnas, filas, ptr_valores);

}


matriz*
matriz_suma(matriz *mtr_a, matriz *mtr_b)
{
    //  Devuelve una nueva matriz, suma de los dos argumentos
    
    if( mtr_a->columna != mtr_b->columna || mtr_a->fila != mtr_b->fila )    return 0;

    size_t col = mtr_a->columna, fl = mtr_b->fila;

    float_t **ptr_suma = malloc(sizeof(float_t*) * fl);

    for( uint8_t i=0; i<fl; i++){
        ptr_suma[i] = malloc(sizeof(float_t) * col);
        for(uint8_t j=0; j<col; j++)
            ptr_suma[i][j] = mtr_a->ptr_valores[i][j] + mtr_b->ptr_valores[i][j];
    }

    return matriz_crear(col, fl, ptr_suma);
}


matriz*
matriz_producto_escalar(matriz *mtr, float_t esc)
{
    if( mtr == NULL ) return NULL;

    float_t **ptr_producto_esc = malloc(sizeof(float_t*) * mtr->fila);
    if(ptr_producto_esc == NULL) return NULL;

    for( uint8_t i=0; i<mtr->fila; i++ )
    {
        ptr_producto_esc[i] = malloc(sizeof(float_t) * mtr->columna);
        if( ptr_producto_esc[i] == NULL )   return NULL;
        for( uint8_t j=0; j<mtr->columna; j++ )
           ptr_producto_esc[i][j] = mtr->ptr_valores[i][j] * esc; 
    }

    return matriz_crear(mtr->columna, mtr->fila, ptr_producto_esc);
}


float_t 
matriz_determinante(matriz *mtr)
{
    /*  Implementacion recursiva
     *  averiguar solucion optimizada si es posible  */
    
    if( mtr->fila != mtr->columna ){
        printf("Imposible determinar para matriz no cuadrada\n");
        return 0;
    }
    return 0;
}


matriz*
matriz_producto_matricial(matriz *mtra, matriz *mtrb)
{
    /*  se computa A x B
     *  algoritmo de producto no optimizado
     *  investigar paralelismo  */
    
    if( mtra == NULL || mtrb == NULL )  return 0;

    //  condicion de producto matricial
    if( mtra->columna != mtrb->fila )   return 0;

    //  arreglos para resultado
    uint8_t producto_filas = mtra->fila;
    uint8_t producto_cols =  mtrb->columna;
    uint8_t i, j, k;
    float **ptr_producto_mat = malloc(sizeof(float*) * producto_filas);

    for( i=0; i<producto_filas; i++ ){
        ptr_producto_mat[i] = malloc(sizeof(float*) * producto_cols);
        for( j=0; j<producto_cols; j++ ){
            ptr_producto_mat[i][j] = 0;
            for( k=0; k<producto_filas; k++ ){
                ptr_producto_mat[i][j] += mtra->ptr_valores[i][k] * mtrb->ptr_valores[k][j]; 
            }
        }
    }

    return matriz_crear(producto_cols, producto_filas, ptr_producto_mat);
}

