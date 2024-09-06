/***************************************************
 * mathgame.c
 * Author: Megan Louie
 * Version: September 6, 2024
 * This program implements a math game that asks a user a series of addition problems 
 * and keeps track of the number of correct responses.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

  int numQuestions;
  int answer;
  int correctAnswers = 0; //number of correct answers will start at 0 at beginning of game
  int userAnswer; 
  int numOne; 
  int numTwo;

  printf("Welcome to Math Game!\n");
  printf("How many rounds would you like to play?\n");
  scanf("%d", &numQuestions);

  //genrates amount of questions user asked for along with the equations
  for (int i =0; i < numQuestions; i++) {
    numOne = rand() % 9 + 1; //makes this a random number between 1-9
    numTwo = rand() % 9 + 1; //makes this a random number between 1-9
    printf("%d + %d = ?\n", numOne, numTwo);
    answer = numOne + numTwo;
    scanf("%d", &userAnswer);
    
    //only increase score if user answer is correct
    if(userAnswer == answer){
      printf("Correct!\n");
      correctAnswers++;
    } 
    else{
      printf("Incorrect :( \n");
    } 
  } 

  printf("You answered %d/%d correctly.\n", correctAnswers, numQuestions);
  return 0;
} 
