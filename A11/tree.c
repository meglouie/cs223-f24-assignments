/*---------------------------------------------
 * Author: Megan Louie
 * Date: 11/21/24
 * Description: implements a binary search tree
---------------------------------------------*/
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree_node* find(const char* name, struct tree_node* root){
  if(root == NULL){
    return NULL;
  }
  if(strcmp(name, root -> data.name) == 0 ){
    return root;
  }
  if(strcmp(name, root -> data.name) < 0){
    return(find( name, root ->left ));
  }
  else{
    return (find(name, root -> right));
  }
}

struct tree_node* insert(const char* name, struct tree_node* root){
 if( root == NULL ){ 
  //create and return a one-node tree
  struct tree_node* newNode = (struct tree_node*) malloc ( sizeof (struct tree_node) );
  if( newNode == NULL )
    printf("Out of space!!! \n");
  else{ 
    strncpy(newNode->data.name, name, sizeof(newNode->data.name) - 1);
    newNode->data.name[sizeof(newNode->data.name) - 1] = '\0'; //ensure null-termination
    newNode->left = NULL;
    newNode->right = NULL;
  }
  return newNode;
  newNode->left = newNode -> right = NULL;
  }
  else 
   if( strcmp(name, root -> data.name) < 0)
   root ->left = insert( name, root ->left );
  else
    if( strcmp(name, root -> data.name) > 0)
    root ->right = insert( name, root->right );
  return root;
}

void clear(struct tree_node* root){
  if(root == NULL){
    return;
  }
  clear(root -> left);
  clear (root -> right);
  free(root);
}

void print(struct tree_node* root){
  if(root == NULL){
    return;
  }
  printf("%s\n", root->data.name);
  print(root->left);
  print(root->right);
}

void printSorted(struct tree_node* root){
  if(root == NULL){
    return;
  }
  printSorted(root -> left);
  printf("%s\n", root->data.name);
  printSorted(root -> right);
}

