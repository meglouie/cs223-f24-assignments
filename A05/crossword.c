/*----------------------------------------------
 * Author: Megan Louie
 * Date: 10/1/24
 * Description: generates a crossword using two words from a user
 * should identify a common letter between the given words 
 * and list one word vertically and the other word horizontally.
 * If there is no common letter, print a message and quit
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int index1 = -1;
int index2;

char *twoD_Array;

/*prints out the crossword
*takes in a 2D array (the crossword), number of rows, and number of columns
*/
void printCrossword(char **crossWord, int row, int col){
  // loops through the rows
  for(int i = 0; i < row ; i++){
    //loops through the columns
    for(int j = 0; j < col ; j++){
      printf("%c", crossWord[i][j]);
    }
    printf("\n");
  }
}

/*function to find a common letter between two words
* takes word1, word2, and pointers to index1 and index2 where common letters will be stored
* Returns 1 if a common letter is found, otherwise returns 0
*/
int findCommon(char* word1, char* word2, int* index1, int* index2){
  // loops through each character in word1
  for(int i = 0; i < strlen(word1); i++ ){
    // loops through each character in word2
    for(int j = 0; j < strlen(word2); j++){
      if(word1[i] == word2[j]){
        *index1 = i; //stores index of matching character for word1
        *index2 = j; //stores index of matching character word2
        return 1;
      }
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
    printf("Usage: %s <word1> <word2>\n", argv[0]);
    exit(0);
  }
  char *word1 = argv[1];
  char *word2 = argv[2];
  int wordIndex1 = -1;
  int wordIndex2 = -1;

  if (!findCommon(word1, word2, &wordIndex1, &wordIndex2)) {
    // If no common letter is found, print message and exit
    printf("No common letter!\n");
    return 0;
  }

  int rows = strlen(word1);
  int cols = strlen (word2);

  //allocates 2D array
  char **crossWord = (char**)malloc(sizeof(char*) * (rows));
    for(int i = 0; i < rows; i++){
      crossWord[i] = (char*)malloc(sizeof(char) * cols);
    }
  // initializes entire grid with dots ('.') for empty spaces
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      crossWord[i][j] = '.';
    }
  }
  
  // places the word1 vertically at the column of the common letter
  for(int i = 0; i < rows; i++){
    crossWord[i][wordIndex2] = word1[i];
  }
  //place the word2 horizontally at the row of the common letter
  for(int j = 0; j < cols; j++){
    crossWord[wordIndex1][j] = word2[j];
  }

  printCrossword(crossWord, rows, cols);

  for(int i = 0; i < rows; i++){
    free(crossWord[i]);
  }

  free(crossWord); //frees all data

  return 0;
}