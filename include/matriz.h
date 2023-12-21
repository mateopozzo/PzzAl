#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include <stddef.h>
#include <stdint.h>
#include <stdint.h>
#include <math.h>

#define MATRIZ_SIZE_MAX 255

typedef struct{
    double_t *arr_val;
    uint8_t columna, fila;
}matriz;

matriz* matriz_crear(size_t col, size_t fl, double_t *arr_val);
void matriz_eliminar(matriz *mtr);
void matriz_consola_imprimir(matriz *mtr);

double_t matriz_determinante(matriz *mtr);
matriz* matriz_inversa(matriz *mtr);
matriz* matriz_suma(matriz *mtr_a, matriz *mtr_b);
matriz* matriz_producto_escalar(matriz *mtr, double esc);
matriz* matriz_producto_matricial(matriz *mtr_a, matriz *mtr_b);
double_t* matriz_autovalores(matriz *mtr);   //  Devuelve arreglo de valores, el primer valor es un entero que indica la cantidad de valores que contiene
matriz* matriz_diagonalizar(matriz *mtr);

#endif

