/***************************************************
 * exclaim.c
 * Author: Megan Louie
 * Version: September 9, 2024
 * This program turns a word into an exclaimation.
 * If the character is a lowercase letter
 * then it replaces it with a randomly chosen character from the set {'@', '!', '#', '*'}
 */

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

int main() {
  char replacements[] = {'@', '!', '#', '*'};
  char buff[32];
  printf("Enter a word: \n");
  scanf("%s", buff);
//loops through each character to see if it contains a lowercase character
//if it contains a lowercase letter it randomly assigns a @, !, #, or *
  for(int i = 0; buff[i] != 0; i++ ){
    if(buff[i] >= 97 && buff[i] <= 122){
      buff[i] = replacements[rand() % 4];
    }
  }
  printf("OMG! %s\n", buff);
  return 0;
}
