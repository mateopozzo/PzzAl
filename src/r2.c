#include <stdint.h>
#include <stdio.h>

/*  setear tamanho de pantalla
 *  y su arreglo de pixeles  */

#define WIDTH 600
#define HEIGHT 600

uint32_t pixel_array[WIDTH*HEIGHT];


// rellena el fondo de la pantalla uniformemente
void
r2_fill(uint32_t * pixel_array, uint32_t color)
{
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++)
            pixel_array[i*WIDTH + j] = color;
    }
}


int
r2_write_ppm(uint32_t *pixel_array, size_t width, size_t height, char *path)
{
    FILE *ppmf = fopen(path, "wb");
    uint8_t pixel_rgb[3];

    if( ppmf == NULL )  return 1;

    fprintf(ppmf, "P6 %zu %zu 255\n", width, height);
    

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            pixel_rgb[0] = pixel_array[i*WIDTH+j] >> 24;
            pixel_rgb[1] = pixel_array[i*WIDTH+j] >> 16;
            pixel_rgb[2] = pixel_array[i*WIDTH+j] >> 8;

            fwrite(pixel_rgb, sizeof(uint8_t), 3, ppmf);
        }
    }

    if(ferror(ppmf)) return 1;

    return 0;
}
/*
int main(){

    r2_fill(pixel_array, 0x0000FFAA);
    r2_write_ppm(pixel_array, WIDTH, HEIGHT, "test.ppm");
    return 0;

}
*/


