/*----------------------------------------------
 * Author: Megan Louie
 * Date: 9/16/2024
 * Description: turns a phrase into ent-speech. 
 * Asks for the pause length and a phrase to change, 
 * and outputs an ent-phrase. 
 * Ent-phrases contain '.' between each letter in the input.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char buff [32];
  int pauseLength;
  char *entPhrase; //pointer for ent phrase
  int length;

  printf("Pause length: \n");
  scanf("%d", &pauseLength);
  printf("Text: \n");
  scanf("%s", buff);
  length = strlen(buff); //gets length of input phrase
  entPhrase = malloc (sizeof(char) * pauseLength * length + length + 1);
  int count = 0; //keep record where we are in entPhrase
  //loops through each character and length and stores in entPhrase
  //count increments to keep track where we are
  for(int i = 0; i < length; i++){
    entPhrase[count] = buff[i];
    count++;
    //after looping through a character from buff then add a '.'
    //'.' is equal to the pauseLength the user inputted 
    //then increment count to know where we are in the entPhrase
    for(int j = 0 ; j < pauseLength; j++){
      entPhrase[count] = '.';
      count++;
    }
  }
  entPhrase[count] = '\0'; //adding terminating character
  printf("entPhrase: %s", entPhrase);
  free(entPhrase);
  return 0;
}