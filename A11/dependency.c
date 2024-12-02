/*----------------------------------------------
 * Author: Megan Louie
 * Date: 11/21/24
 * Description: implement a program that uses N threads to 
 * build a binary search tree of a given set of files.
 * the program should give the user a prompt where they can list the 
 * processed files in alphabetical order and 
 * then query the dependencies of the file by giving the filename.
---------------------------------------------*/
#include <stdio.h>
#include "tree.h"
#include "stdlib.h"
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

struct thread_data{
 pthread_t tid;
 int start;
 int files;
 char **argv;
 int index;
 struct tree_node** root;
};

pthread_mutex_t mutex;

void *tree(void *userData){
  struct thread_data *data = (struct thread_data*) userData;
  data->tid = pthread_self();
  printf("Thread %d is processing %d files starting at index %d\n", 
  data->index, data->files, data->start);
  //loops through files assigned to this thread
  for (int i = data->start; i < data->start + data->files; i++) {
    pthread_mutex_lock(&mutex);
    *(data->root) = insert(data->argv[i], *(data->root));
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(int argc, char **argv){
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  if (argc < 3){
    printf("not enough arguments! \n"); 
  }
  int numThreads = atoi(argv[1]);
  int totFiles = argc - 2;
  printf("processing %d files\n", totFiles);
  //allocate memory for the file names
  char **files = (char **)malloc(totFiles * sizeof(char *));
  for (int i = 0; i < totFiles; i++){
    files[i] = (char *)malloc(100 * sizeof(char));
  }
  //copy file names from command-line arguments
  for (int i = 0; i < totFiles; i++){
    strncpy(files[i], argv[i+2], 100);
  }
  int filePerThread;
  int extraFiles = totFiles % numThreads;
  if (totFiles % numThreads != 0){
    extraFiles = totFiles % numThreads;
  }
  filePerThread = totFiles / numThreads;
  pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
  struct thread_data *threadData = malloc(numThreads * sizeof(struct thread_data));
  pthread_mutex_init(&mutex, NULL);
  struct tree_node* root = NULL;
  int count = 0; //keeps track of how many threads assigned an extra file
  int start = 0;
  //distribute files among threads and create threads
  for (int i = 0; i < numThreads; i++){
    int numFiles = filePerThread;
    if (count < extraFiles) {
      numFiles++;
      count++;
    }
    threadData[i].index = i;
    threadData[i].files = numFiles;
    threadData[i].argv = files;
    threadData[i].start = start;
    threadData[i].root = &root;
    pthread_create(&threads[i], NULL, tree, (void*) &threadData[i]);
    start += numFiles;
  }
  for (int i = 0; i < numThreads; i++){
    pthread_join(threads[i], NULL);
  }
  printf("threads have finished processing\n");
  gettimeofday(&tend, NULL);
  float timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec -tstart.tv_usec)/1.e6;
  printf("Elapsed Time is %.6f seconds\n",timer);
  //read files
  char input[150];
  while(1){
    scanf("%s", input);
     if (strcmp(input, "list") == 0){
      printSorted(root);
    } 
    else if (strcmp(input, "quit") == 0){
      break;
    }
    else{
      struct tree_node* file = find(input, root);
      if(file == NULL){
        printf("%s not found \n", input);
      }
      else{
        printf(" %s has the following dependencies\n", input);
        FILE *infile ;
	      infile = fopen(file->data.name, "r");
        char lines[150];
        while(fgets(lines, 150, infile) != NULL){
          if(strstr(lines, "#include")){
            char dependcy [150];
            char *start = strchr(lines, '"');
             if (start){
              char *end = strchr(start + 1, '"');
              int length = end - start - 1;
              strncpy(dependcy, start + 1, length);
              dependcy[length] = '\0'; 
              printf("%s\n", dependcy);
            } 
            else{
              char *start = strchr(lines, '<');
              char *end = strchr(start + 1, '>');
              int length = end - start - 1;
              strncpy(dependcy, start + 1, length);
              dependcy[length] = '\0'; 
              printf("%s\n", dependcy);
            }
          }
        }
        fclose(infile);
      }
    }
  }
  clear(root);
  pthread_mutex_destroy(&mutex);
  for(int i=0; i< totFiles; i++){
    free(files[i]);
	}
  free(files);
  free(threadData);
  free(threads);
  return 0;
}
