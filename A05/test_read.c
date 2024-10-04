/*----------------------------------------------
 * Author: Megan Louie
 * Date: 10/3/24
 * Description: test file that tests the read function made in read_ppm.c
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

  // todo: print out the grid of pixels
  for(int i = 0; i < w; i ++){
    for(int j = 0; j < h; j++){
      printf("(%d, %d, %d) ", pixels[i*w + j].red, pixels[i*w + j].green, pixels[i*w + j].blue);
    }
    printf("\n");
  }
  free(pixels);
  return 0;
}

