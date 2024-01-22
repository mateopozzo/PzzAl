#include "../include/matriz.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*================================================================================================*/
// Funciones y macros de aplicacion interna
#define DET2X2(M)   M[0][0] * M[1][1] - \
                    M[1][0] * M[0][1]

#define SARRUS(M)   M[0][0] * M[1][1] * M[2][2] * +\
                    M[1][0] * M[2][1] * M[0][2] * +\
                    M[2][0] * M[0][1] * M[1][2] * -\
                    M[2][0] * M[1][1] * M[0][2] * -\
                    M[1][0] * M[0][1] * M[2][2] * -\
                    M[0][0] * M[2][1] * M[1][2]


void
swap(float_t *a, float *b)
{
    float c = *a;
    *a = *b;
    *b = c;
}


void
_opel_fila_suma(matriz* mtr, uint fila1, uint fila2, float_t *escalar)
{
    if(!(*escalar)){
        printf("Operacion no valida para escalar nulo");
        return;
    }

    float_t *resultado = mtr->ptr_valores[fila1];
    float_t *operando = mtr->ptr_valores[fila2];
    for( float_t *end = mtr->ptr_valores[fila1]+mtr->columna; resultado != end; resultado++){
        *resultado += *escalar * *operando;
        operando++;
    }
}


void
_opel_fila_intercambio(matriz *mtr, uint fila1, uint fila2)
{
    float_t *fila_a = mtr->ptr_valores[fila1];
    float_t *fila_b = mtr->ptr_valores[fila2];
    float_t *fila_c = fila_a;
    fila_a = fila_b;
    fila_b = fila_c;
}


/*================================================================================================*/
/*================================================================================================*/
//  implementacion de biblioteca


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
    if( !mtr ) return;

    for( uint8_t i=0; i<mtr->fila; i++ ){
       free(mtr->ptr_valores[i]);
       mtr->ptr_valores[i] = NULL;
       printf("%d\n", i);
    }

    free(mtr->ptr_valores);
    mtr->ptr_valores = NULL;
    free(mtr);
    mtr = NULL;
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

/*   
 *   las siguientes funciones realizan operaciones del conjunto Mnxn,
 *   devuelven un puntero a una nueva matriz, sin sobreescribir la
 *   la anterior  
*/

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

uint8_t
matriz_determinante(matriz *mtr, float_t *det)
{
    /*  Retorna falso (0) si la matriz no es cuadrada
     *  Aprovechar propiedad de matriz triangular  
     *  1 - Detectar si hay linea nula  
     *  2 - Triangular matriz con operaiones elementales
     *  3 - Producto de elementos de diagonal por escalar*/

    if( mtr->fila != mtr->columna ){
        printf("Imposible determinar para matriz no cuadrada\n");
        return 0;
    }
    
    //  Soluciones especificas para matrices de 2x2 y 3x3
    if( mtr->fila == 2 && mtr->columna == 3 ){
        *det = DET2X2(mtr->ptr_valores);
        return 1;
    }

    if( mtr->fila == 3 && mtr->columna == 3 ){
        *det = SARRUS(mtr->ptr_valores);
        return 1;
    }

    //  Verifico si es posible crear alguna linea nula
    //  Algoritmo de recorrido anotando posiciones nulas
    //  Considero que alguna linea contiene un 0 hasta que se demuestre el contrario
    
    uint8_t *filas_con_valor_nulo = malloc(sizeof(int) * mtr->columna);
    uint8_t *columnas_con_valor_nulo = malloc(sizeof(int) * mtr->fila);
    uint8_t linea_nula = 1;
    uint8_t i, j;

    for( i=0; i<mtr->fila; i++ )
        filas_con_valor_nulo = columnas_con_valor_nulo = 0;
    
    //  Recorro la matriz
    for( i=0; i<mtr->fila; i++ ){
        for( j=0; j<mtr->columna; j++){
            if(!(mtr->ptr_valores[i][j])){
                filas_con_valor_nulo[i] = 1;
                columnas_con_valor_nulo[j] = 1;
            }
        }
    }

    i=j=0;
    while( i<mtr->fila && linea_nula ){
        if( !filas_con_valor_nulo[i] )
            linea_nula = 0;
        i++;
    }
        
    if( linea_nula ){
        *det = 0;
        return 1; 
    }
    linea_nula = 1;
        
    while( j<mtr->fila && linea_nula ){
        if( !columnas_con_valor_nulo[j] )
            linea_nula = 0;
        j++;
    }

    if( linea_nula ){
        *det = 0;
        return 1; 
    }

    //  Finalmente, si no se encontro alguna 
    //  posible linea nula, se procede a triangular la matriz



    return 1; 
    
}

matriz *
matriz_triangular(matriz *mtr)
{
    /*  Recibe una matriz y la triangula mediante operaciones elementales  */
    matriz * mtr_triangular = matriz_crear(mtr->columna, mtr->fila, mtr->ptr_valores);
    
    //  Reviso que no haya ceros en diag ppal
    //  Se le suma alguna fila que desanule el valor
    for( uint i = 0; i < mtr->fila; i++  ){
        if( !mtr->ptr_valores[i][i] ){
            //  Busco alguna fila que se pueda sumar a esta
            uint j = 0;
            while( !mtr->ptr_valores[j][i] && j < mtr->fila ) j++;

            float_t k = 1;
            _opel_fila_suma(mtr, i, j, &k);
        }
    }


    
    return mtr_triangular;
}

