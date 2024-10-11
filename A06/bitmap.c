/*----------------------------------------------
 * Author: Megan Louie
 * Date: 10/8/24
 * Description: reads in a single 64-bit unsigned integer
 * and outputs it as an 8x8 1bpp sprite
 ---------------------------------------------*/
#include <stdio.h>

int main()
{
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);
  //loops through the first 64 bits of the img value
  for (int i = 1; i <= 64; i++){
    //creetes a mask by shifting 1 to the left by (63 - i + 1) positions
    //isolates individual bits from the left
    unsigned long leftMask = 0x1ul << (63 - i + 1);
    unsigned long left = (leftMask & img);
    // if result is non-zero then the bit is 1, print "1"
    if (left){
      printf("1");
    }
    //the bit is 0, print "0"
    else{
      printf("0");
    }
    //print new line after every 8 bits to format as bytes
    if (i % 8 == 0){
      printf("\n");
    }
  }
  return 0;
}
