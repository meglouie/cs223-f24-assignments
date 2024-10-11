/*----------------------------------------------
 * Author: Megan Louie
 * Date: 10/10/24
 * Description: reads in a PPM file (raw, or binary, format) 
 * and then outputs any message that might be stored 
 * in the least significant bits of each color.
 * Your program should read bits 
 * from each of the red, green, and blue colors 
 * — top to bottom, left to right
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h);
  unsigned char* pixelInfo = (unsigned char*)pixels; //cast pixels array to an unsigned char pointer
  int total = ((w * h) * 3)/8; //calculates max number of characters that can be stored in the image
  printf("Reading %s with width %d and height %d \n", argv[1], w, h);
  printf("Max number of characters in the image: %d\n", total);
  char* result = malloc(total * 8); // allocates memory to store the decoded message 
  unsigned char tempChar; // Temp variable to store each decoded character
  unsigned char mask = 0b1; //mask to extract the least significant bit
  unsigned char bit; //stores individual bits extracted from the image
  //loops through the pixel data 
  for(int i = 0; i < total * 8; i++){
    bit = pixelInfo[i]&mask;
    tempChar = (tempChar << 1) | bit; //shifts tempChar to the left and add the new bit
    //every 8 bits form a complete character thenstore it in the result
    if(i % 8 == 7){
      result[i/8] = tempChar;
      //if decoded character is the terminating character then break
      if(tempChar == '\0'){
        break;
      }
      tempChar = 0;
    }
  }
  printf("%s\n", result);
  free(result);
  free(pixels);
  return 0;
}
