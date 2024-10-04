/*----------------------------------------------
 * Author: Megan Louie
 * Date: 10/4/24
 * Description: tests the function from write_ppm.c
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

  // test writing the file to test.ppm, reload it, and print the contents
  write_ppm("test.ppm", pixels, w, h);
  free(pixels);
  pixels = read_ppm("test.ppm", &w, &h);
  for(int i = 0; i < w; i ++){
    for(int j = 0; j < h; j++){
      printf("(%d, %d, %d) ", pixels[i*w + j].red, pixels[i*w + j].green, pixels[i*w + j].blue);
    }
    printf("\n");
  }
  free(pixels);
  return 0;
}
