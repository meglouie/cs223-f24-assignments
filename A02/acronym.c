/***************************************************
 * acronym.c
 * Author: Megan Louie
 * Version: September 9, 2024
 * This program computes an acronym from a given phrase. 
 * It should create a string consisting of all capital letters from the given phrase.
 */

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

int main() {
  char phrase[1024]; //holds the input phrase
  char upperCase[1024]; //stores extracted uppercase letters
  printf("Enter a phrase: \n");
  scanf("%[^\n]%*c", phrase);
  int capitalLetters = 0; // intializes counter to keep track of the number of capital letters found
  // Loop through each character to check for uppercase letters
  for(int i = 0; i < 1024; i++){
    // Checks if the end of the string has reached terminating character
    if(phrase[i]=='\0'){
      upperCase[capitalLetters] = '\0';
      break;
    }
    // Checks if the current character is an uppercase letter
    // If the character is uppercase, add it to the 'upperCase' array
    if(phrase[i] >= 65 && phrase[i] <= 90){
      upperCase[capitalLetters] = phrase[i];
      capitalLetters++; // Increments counter to move to the next position
    }
  }
  printf("Your acronym is %s \n", upperCase);
  return 0;
}
