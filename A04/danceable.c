/*----------------------------------------------
 * Author: Megan Louie
 * Date: 9/23/24
 * Description: allows users to easily access the most danceable songs in songlist.csv
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct node{
  struct songList element; //node of elements of struct songList
  struct node* next; //points to next node
};

/*
*inserts a node infront of another in the linked list
*/
struct node* insertFront(struct songList element, struct node* head){
  struct node* n = malloc(sizeof(struct node));
  if(n == NULL){
    printf("ERROR: Out of space \n");
    exit(1);
  }
  n->element = element;
  if(head==NULL){
    n -> next = NULL;
    return n;
  }
  n->next = head;
  return n;
}

/*
*removes a node in the linked list
*/
void removeNode(struct node* parentNode){
  struct node* temp = parentNode -> next;
  if (temp == NULL){
    printf("Error");
  } 
  else {
    struct node* temp2 = temp -> next;
    parentNode -> next = temp2;
    free(temp); // Free the removed node
  }
}

/*
*prints the most danceable song out with its other attributes
*/
void printDanceable(struct node* mostDanceable){
  printf("%-20s %-20s %02d:%02d      %-15.3f %-12.3f %-12.3f %-12.3f\n",
  mostDanceable -> element.song, mostDanceable-> element.artist, mostDanceable -> element.durationMin, 
  mostDanceable -> element.durationSec, mostDanceable -> element.danceability, 
  mostDanceable -> element.energy, mostDanceable -> element.tempo, mostDanceable -> element.valence);
}

/*
*prints the song list
*/
void printSongs(struct node* songs) {
  printf("Song List:\n");
  printf("ID) %-20s %-20s %-10s %-15s %-12s %-12s %-12s \n", "Title", 
  "Artist", "Duration", "Danceability",
  "Energy", "Tempo", "Valence");
  struct node* temp = songs;
  //Loops through each song in the array and print its details
  int i = 0;
  while(temp != NULL){
    printf("%d)", i);
    printDanceable(temp);
    temp = temp -> next;
    i++;
  }
}

/*
*when declared it frees all data aka songs in the list
*/
void clearList(struct node* head) {
  struct node* temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

/*
*finds the song with the greatest danceability
*/
struct node* findDanceability(struct node* head) {
  if (head == NULL) {
    printf("Error: List is empty.\n");
    return head;
  }
  struct node* max = head;
  struct node* temp = head;
  struct node* temp2 = NULL;  // Keep track of the previous node
  struct node* parentNode = NULL;
  while (temp != NULL) {
    if (temp->element.danceability > max->element.danceability) {
      max = temp;
      parentNode = temp2;
    }
    temp2 = temp;
    temp = temp->next;
  }
  printf("Most Danceable Song:\n");
  printDanceable(max);  // Print the song details before removing it
  // Remove the most danceable node from the list
  if (max == head) {
    head = head->next;  // Move head if the max is the first node
  } 
  else if (parentNode != NULL) {
    parentNode->next = max->next;  // Bypass the max node
  }
  free(max);  // Free the node after removing it from the list
  max = NULL; // Set it to NULL to avoid dangling pointer issues
  return head;
}

/*
*opens and reads in csv file
*/
struct node* readSongFile (){
  FILE *infile; 
  infile = fopen("songlist.csv", "r");
  // if nothing in the file then exit out of loop
  if (infile == NULL){
    printf("Error: unable to open the file %s\n", "songlist.csv");
    exit(1);
  }
  char buffer[100];
  fgets(buffer, 100, infile);
  //struct songList* song = malloc(sizeof(struct songList));
  struct node* songHead = NULL;
  //loops through each songs
  while(fgets(buffer, 100, infile)!=NULL){
    struct songList song;
    char* attribute = strtok(buffer, ",");
    //Copy the song title to the 'song' field of the 'list' array at the current index
    //does this for all attributes in the file
    strcpy(song.song, attribute);
    attribute = strtok(NULL,",");
    strcpy(song.artist, attribute);
    attribute = strtok(NULL,",");
    int durMS = atoi (attribute);
    //Convert the duration from milliseconds to seconds
    //stores the duration values in their respective places
    durMS = durMS/1000;
    song.durationSec = durMS % 60;
    song .durationMin = durMS/60;
    attribute = strtok(NULL,",");
    //Extract and convert the next attribute (danceability) to a float, then store it
    song . danceability = atof(attribute);
    attribute = strtok(NULL,",");
    //Extract and convert the next attribute (energy) to a float, then sto
    song. energy = atof(attribute);
    attribute = strtok(NULL,",");
    //Extract and convert the next attribute (tempo) to a float, then store it
    song. tempo = atof(attribute);
    //Extract and convert the next attribute (valence) to a float, then store it
    attribute = strtok(NULL,",");
    song.valence = atof(attribute);
    songHead = insertFront(song,songHead);
  }
  fclose(infile); //Closes the input file after reading all the data
  return songHead;
}

int main() {
  struct node* songs = readSongFile();
  while(1){
    char input[2];
    printSongs(songs);
    printf("Press 'd' to show the most danceable song (any other key to quit): \n");
    scanf("%s", input);
    if(strcmp(input,"d")!=0){
      break;
    }
    songs = findDanceability(songs);
  }
  clearList(songs);
  return 0;
}
