/*----------------------------------------------
 * Author: Megan Louie
 * Date: 11/21/24
 * Description: implements a simplified version of the bash command grep. 
 * Grep searches a list of files for a given keyword or expression
---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

struct thread_data{
 pthread_t tid;
 char **files;
 char **argv;
 int numFiles;
 int start;
 int count;
 int index;
 char *keyword;
 int linesFound;
 int matchesFound;
};

pthread_mutex_t mutex;

void *grep(void *userData){
  struct thread_data *data = (struct thread_data *) userData;
  int count = 0;
  FILE *infile;
  char buffer[100];
  //loops files assigned to the thread
  for(int i = data -> start; i < data -> start + data -> count; i++){
    infile = fopen(data -> files[i], "r");
    if(infile == NULL){
      printf("Error!\n");
      continue;
    }
    int lines = 0;
    int matches = 0;
    //reads files
    while(fgets(buffer, sizeof(buffer), infile)){
      lines++;
      if(strstr(buffer, data ->keyword)){
        matches++;
      }
    }
    fclose(infile);
    pthread_mutex_lock(&mutex);
    printf("Thread %ld: file %s, lines: %d, matches: %d \n", (unsigned long) data ->tid, 
    data ->files[i], lines, matches);
    pthread_mutex_unlock(&mutex);
    //updates line and match counts
    data ->linesFound += lines;
    data -> matchesFound += matches;
  }
  return NULL;
}

int main(int argc, char **argv) {
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  if(argc < 4){
    printf("No files were input\n");
    exit(0);
  }
  int numThreads = atoi(argv[1]);
  char *keyword = argv[2];
  char **files = &argv[3];
  int numFiles = argc - 3; //gives count of arguments after the first three
  if(numThreads <= 0){
    printf("num of threads has to be greater than 0 \n");
    exit (0);
  }
  struct thread_data *threadData = malloc(sizeof(struct thread_data) * numThreads);
  pthread_mutex_init(&mutex, NULL); //initalizse mutex
  int filesperThread = numFiles/numThreads;
  int filesExtra = numFiles % numThreads;
  int currentFile = 0;
  //create threads and assign files to them
  for(int i = 0; i < numThreads; i++){
    threadData[i].files = files;
    threadData[i].numFiles = numFiles;
    threadData[i].start = currentFile;
    threadData[i].index = currentFile;
    threadData[i].count = filesperThread;
    if (i < filesExtra) { // updates the current file so index isn't weird
      threadData[i].count++;
    }
    currentFile += threadData[i].count;
    threadData[i].keyword = keyword;
    threadData[i].linesFound = 0;
    threadData[i].matchesFound = 0;
    pthread_create(&threadData[i].tid, NULL, grep, &threadData[i]);
  }
  int totalLines = 0;
  int totalMatches = 0;
  //wait for all threads to finish
  for(int i = 0; i < numThreads; i++){
    pthread_join(threadData[i].tid, NULL);
    totalLines += threadData[i].linesFound;
    totalMatches += threadData[i].matchesFound;
  }
  printf("Total Lines: %d, Total Matches: %d \n", totalLines, totalMatches);
  gettimeofday(&tend, NULL);
  float timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec -tstart.tv_usec)/1.e6;
  printf("Elapsed Time is %.6f seconds\n",timer);
  pthread_mutex_destroy(&mutex);
  free(threadData);
  return 0;
}