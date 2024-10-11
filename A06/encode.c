/*----------------------------------------------
 * Author: Megan Louie
 * Date: 10/10/24
 * Description: reads in a PPM file (raw, or binary, format) 
 * and asks the user for a message to embed within it.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  //read ppm file and store its pixel data in pixels array
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h);
  unsigned char* pixelInfo = (unsigned char*)pixels; 
  //checks if the file was read successfully
   if (pixels == NULL) {
    printf("Error: Could not read file %s\n", argv[1]);
    return 1;
    }
  int total = ((w * h) * 3)/8;
  printf("Reading %s with width %d and height %d \n", argv[1], w, h);
  printf("Max number of characters in the image: %d\n", total);
  char *phrase = malloc(sizeof(char)*total); //allocates memory for the phrase to be encoded
  printf("Enter a phrase:\n");
  scanf("%[^\n]", phrase);
  unsigned char newColor;
  unsigned char mask = 0b1; 
  unsigned char bit;
  //loops through the pixel data to embed the message bit by bit
  for(int i = 0; i < total * 8; i++){
    bit = pixelInfo[i]&mask;
    //beyond the phrase length, set the bit to 0 
    if(i >= strlen(phrase) * 8){
      bit = 0;
    }
    //extract current bit from phrase to encode it
    else{
     bit = (phrase[i/8] >> (7 - i % 8)) & 0b1;
    }
    newColor = (pixelInfo[i] & ~mask) | bit; //sets new color value by updating 
    pixelInfo[i] = newColor; 
  }
  //creates a new filename for the encoded output file
  char output_filename[256];
  strcpy(output_filename, argv[1]); 
  char *dot = strrchr(output_filename, '.');
  if (dot != NULL) {
        strcpy(dot, "-encoded.ppm");  //overwrite from the dot position
    } else {
        strcat(output_filename, "-encoded.ppm"); //in case there's no extension
    }
  write_ppm("feep-raw-encoded.ppm", pixels, w, h);
  printf("Writing file feep-raw-encoded.ppm \n");
  free(pixels);
  free(phrase);
  return 0;
}

