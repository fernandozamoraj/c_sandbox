#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "linkedlist.h"
/*
  -------List functions----------

*/
Node_t* createLink(){
  Node_t* newLink = malloc(sizeof(Node_t));
  
  if(newLink != NULL){
    newLink->next = NULL;
    newLink->data = NULL; 
  }
  
  return newLink;
}

Node_t* findNode(char* key, Node_t* list){
  
  Node_t* temp = list;
  
  while(temp != NULL){
    if(strcmp(key, temp->key) == 0){
      return temp;
    }
    temp = temp->next;
  }
  
  return temp;
}

Node_t* addNode(char* key, DATA* data, Node_t* list){
  Node_t* node = createLink();
  Node_t* tail = NULL;
  
  node->key = strdup(key);
  node->data = data;
  
  tail = getTail(list);
  tail->next = node;
  
  return node;
}

Node_t* getTail(Node_t* list){
  
  Node_t* temp = list;
  Node_t* tail = list;
  
  if(temp != NULL){
    while(tail->next != NULL){
      tail = tail->next;
    }  
  }
  
  return tail;
}

void displayListInt(Node_t* list){
  Node_t* temp = list;
  int *value = 0;
  
  while(temp != NULL){
    value = temp->data;
    printf("\n%d %s", *value, temp->key);
    temp = temp->next;
  }
}

void displayListString(Node_t* list){
  Node_t* temp = list;
  char *value;
  
  while(temp != NULL){
    value = temp->data;
    printf("\n%s %s", value, temp->key);
    temp = temp->next;
  }
}


void displayList(void (*displayFunc)(char*, DATA*), Node_t* list){
  Node_t* temp = list;
  char *value;
  
  while(temp != NULL){
    (*displayFunc)(temp->key, temp->data);
    temp = temp->next;
  }
}


void deleteList(Node_t* list){
  
  Node_t* temp = list;
  Node_t* next = list;
  
  while(temp != NULL){
    next = temp->next;
  
    DEBUGLOG("\nDeleting %s...", temp->key);

    //Key and data are dynamic so they must
    //be freed.
    free(temp->key);
    free(temp->data);
    free(temp);

    temp = next;
  }
}

int countList(Node_t* list){
  Node_t* temp = list;
  char *value;
  int count = 0;
  
  while(temp != NULL){
    temp = temp->next;
    count++;
  }

  return count;
}