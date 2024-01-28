#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include <stddef.h>
#include <stdint.h>
#include <math.h>

#define MATRIZ_SIZE_MAX 255

typedef struct matriz{
    float_t **ptr_valores;
    uint8_t fila;
    uint8_t columna;
}matriz;

matriz* matriz_crear(size_t col, size_t fl, float_t **ptr_valores);
void matriz_eliminar(matriz *mtr);
matriz* matriz_consola_cargar(void);
void matriz_consola_imprimir(matriz *mtr);

uint8_t matriz_determinante(matriz *mtr, float_t *det);
matriz* matriz_inversa(matriz *mtr);
matriz* matriz_suma(matriz *mtr_a, matriz *mtr_b);
matriz* matriz_producto_escalar(matriz *mtr, float_t esc);
matriz* matriz_producto_matricial(matriz *mtr_a, matriz *mtr_b);
float_t* matriz_autovalores(matriz *mtr);   //  Devuelve arreglo de valores, el primer valor es un entero que indica la cantidad de valores que contiene
matriz* matriz_triangular(matriz *mtr);
matriz* matriz_diagonalizar(matriz *mtr);

#endif

