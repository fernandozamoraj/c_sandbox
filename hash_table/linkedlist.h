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

Node_t* createLink();

Node_t* findNode(char* key, Node_t* list);

Node_t* addNode(char* key, DATA* data, Node_t* list);

Node_t* getTail(Node_t* list);

/*
*  Deletes all dynamically allocated data in the table.
*  This includes the key, data and each node within the
*  the list, to include the list.
*/
void deleteList(Node_t* list);

void displayListInt(Node_t* list);

void displayListString(Node_t* list);
#endif