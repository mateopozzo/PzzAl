#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdint.h>
#include <math.h>

#define SIZE_MAX_VECTOR 255

typedef struct vector{
    float_t *arreglo_valores;
    size_t n_dim;
}vector;



#endif
