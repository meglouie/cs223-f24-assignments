/*----------------------------------------------
 * Author: Megan Louie
 * Date: 9/18/24
 * Description: reads songs from a text file into an array
 * also reads the danceability, energy, tempo, and valence from the csv file
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

struct songList{
  char song[32]; //title of song
  char artist[32]; //artist name
  int durationMin; //duration of song in minutes
  int durationSec; //duration of song in seconds
  float danceability; //the danceability of the song
  float energy; //measure of intensity and activity
  float tempo; //overall estimated tempo of a track in beats per minute 
  float valence; //describes the musical positiveness conveyed by a trac
};

struct songList* readSongFile (){
  FILE *infile; 
  infile = fopen("songlist.csv", "r");
  if (infile == NULL){
    printf("Error: unable to open the file %s\n", "songlist.csv");
    exit(1);
  }
  char buffer[100];
  fgets(buffer, 100, infile);
  char* token = strtok(buffer,",");
  int songNumber = atoi (token);
  fgets(buffer, 100, infile);
  struct songList* list = malloc(songNumber * sizeof(struct songList));
  for(int i = 0; i < songNumber; i++){
    fgets(buffer, 100, infile);
    char* attribute = strtok(buffer, ",");
    strcpy(list[i].song, attribute);
    attribute = strtok(NULL,",");
    strcpy(list[i].artist, attribute);
    attribute = strtok(NULL,",");
    int durMS = atoi (attribute);
    durMS = durMS/1000;
    list[i].durationSec = durMS % 60;
    list[i].durationMin = durMS/60;
    attribute = strtok(NULL,",");
    list[i].danceability = atof(attribute);
    attribute = strtok(NULL,",");
    list[i].energy = atof(attribute);
    attribute = strtok(NULL,",");
    list[i].tempo = atof(attribute);
    attribute = strtok(NULL,",");
    list[i].valence = atof(attribute);
  }
  fclose(infile);
  return list;
}

/*
* Function to print the list of songs in a table format
*/
void printSongs(struct songList* songs, int numSongs) {
  printf("Song List:\n");
  printf("ID) %-20s %-20s %-10s %-15s %-12s %-12s %-12s \n", "Title", 
  "Artist", "Duration", "Danceability",
  "Energy", "Tempo", "Valence");
  //Loops through each song in the array and print its details
  for (int i = 0; i < numSongs; i++) {
    printf("%d) %-20s %-20s %02d:%02d      %-15.3f %-12.3f %-12.3f %-12.3f\n",
    i, songs[i].song, songs[i].artist, songs[i].durationMin, 
    songs[i].durationSec, songs[i].danceability, songs[i].energy,
    songs[i].tempo, songs[i].valence);
  }
}

int main() {
  printf("Welcome to Megan's Dynamic Song List! \n");
  struct songList* list= readSongFile();
  printSongs(list, 18);
  free(list);
  return 0;
}
