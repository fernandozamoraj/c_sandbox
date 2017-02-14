#include<stdio.h>
#include "consts.h"
#include "debug.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//In reality this shouldbe separate from Node
//key and data should be should in a KeyValue pair
//and and a node should contain that as nested struct
typedef struct Node{
  char* key;
  DATA* data; 
  struct Node* next;
} Node_t;


/*
   --------List Functions---------------
*/

/*
   createLink - dynamically allocates memory for a Node_t type 
   creates a type of Node_t* and returns it
*/
Node_t* createLink();

/*
   Finds the node for the given key
*/
Node_t* findNode(char* key, Node_t* list);

/*
  Adds a node for the given key with the given data
*/
Node_t* addNode(char* key, DATA* data, Node_t* list);

/*
  Gets the last node in the list.  It returns a node
  unless the list is emtpy
*/
Node_t* getTail(Node_t* list);

/*
*  Deletes all dynamically allocated data in the table.
*  This includes the key, data and each node within the
*  the list, to include the list.
*/
void deleteList(Node_t* list);

/*
  Displays the list as integers if the data holds ints
  This can better be change to be dynamic by passign a 
  function pointer to display the list of whatever type
*/
void displayListInt(Node_t* list);

/*
  Displays the list as strings if the data holds ints
  This can better be change to be dynamic by passign a 
  function pointer to display the list of whatever type
*/
void displayListString(Node_t* list);

void displayList(void (*displayFunc)(char*, DATA*), Node_t* list);

int countList(Node_t* list);

#endif