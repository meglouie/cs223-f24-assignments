/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *infile; 
  infile = fopen(filename, "r");
  // if nothing in the file then exit out of loop
  if (infile == NULL){
    printf("Error: unable to open the file %s\n", filename);
    exit(1);
  }
  char ppm [4];
  fgets(ppm, 4, infile);
  char ppm2[100];
  fgets(ppm2, 100, infile);
  int maxValue;
  fscanf(infile, "%d %d\n%d\n", w, h, &maxValue);
  struct ppm_pixel* data = malloc(sizeof(struct ppm_pixel) * (*w * *h));
  fgets((char*)data, sizeof(struct ppm_pixel) * (*w * *h), infile);
  fclose(infile);
  return data;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
