/***************************************************
 * songs.c
 * Author: Megan Louie
 * Version: September 11, 2024
 * This program fills an array with three or more songs 
 * and then allows the user to edit the data in the array.
 */

#include <stdio.h>
#include <string.h> 

struct songList{
  char song[32]; //title of song
  char artist[32]; //artist name
  int durationMin; //duration of song in minutes
  int durationSec; //duration of song in seconds
  float danceability; //the danceability of the song
};

/*
* Function to print the list of songs in a table format
* Takes an array of songList and the number of songs as input
*/
void printSongs(struct songList songs[], int numSongs) {
  printf("Song List:\n");
  printf("ID) %-20s %-20s %-10s %-15s\n", "Title", "Artist", "Duration", "Danceability");
  //Loops through each song in the array and print its details
  for (int i = 0; i < numSongs; i++) {
    printf("%d) %-20s %-20s %02d:%02d      %-15.2f\n",
    i, songs[i].song, songs[i].artist, songs[i].durationMin, 
    songs[i].durationSec, songs[i].danceability);
  }
}

/*
* Function to allow the user to edit a song's details
* Takes an array of songList and the number of songs as input
*/
void editSongs(struct songList songs[], int numSongs) {
  printf("What song would you like to edit (Enter song ID)? ");
  int songNumber;
  scanf("%d%*c", &songNumber); 
  // Checks if the song number is valid
  if (songNumber < 0 || songNumber >= numSongs) {
    printf("Invalid song ID.\n");
    return; // Exit if ID is invalid
  }
  printf("Which attribute do you wish to edit? [artist, title, duration, danceability]: ");
  char attribute[15];
  scanf("%s%*c", attribute);
  // Checks which attribute the user wants to edit and updates accordingly
  if (strcmp(attribute, "artist") == 0) {
    char artist[32]; //temporarily stores info
    printf("Enter a new artist: ");
    scanf("%[^\n]%*c", artist);
    strcpy(songs[songNumber].artist, artist); // Update the artist in the song array
  } 
  else if (strcmp(attribute, "title") == 0) {
    char title[32]; //temporarily stores info
    printf("Enter a new title: ");
    scanf("%[^\n]%*c", title);
    strcpy(songs[songNumber].song, title); // Update the title in the song array
  } 
  else if (strcmp(attribute, "duration") == 0) {
    int durationMin, durationSec; //temporarily stores info
    printf("Enter a new duration (minutes): ");
    scanf("%d", &durationMin);
    printf("Enter a new duration (seconds): ");
    scanf("%d", &durationSec);
    songs[songNumber].durationMin = durationMin; // Updates minutes
    songs[songNumber].durationSec = durationSec; // Updates seconds
  } 
  else if (strcmp(attribute, "danceability") == 0) {
    float danceability; //temporarily stores info
    printf("Enter new danceability: ");
    scanf("%f", &danceability);
    songs[songNumber].danceability = danceability; //updates danceability
  } 
  else {
  printf("Invalid attribute.\n"); //if atrribute user typed doesn't exist print out this
  }
}

int main() {
  // Initialize a list of songs
 struct songList songs[3] = {
    {"Magnetic", "ILLIT", 2, 40, 0.79},
    {"SPOT!", "ZICO, JENNIE", 2, 47, 0.87},
    {"OMG", "NewJeans", 3, 32, 0.80}
  };
  printf("Welcome to Megan's Songlist! \n");
  int numSongs = 3; //number of songs in array
  printSongs(songs, numSongs); // prints list of songs before editing
  editSongs(songs, numSongs); // lets user edit a song's details
  printf("\nUpdated Song List:\n");
  printSongs(songs, numSongs);
  return 0;
}
