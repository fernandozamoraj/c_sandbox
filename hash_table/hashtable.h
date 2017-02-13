#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "consts.h"
#include "debug.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H
/*
   Hashtable implementation
   requirements
   1. Hold any data type (void *)
   2. 
*/





/*
    -----------Hashtable functions----------------
*/


unsigned long hash(unsigned char* str);

int getHash(char* str);

void displayTableInt(Node_t* hashTable[]);

void displayTableString(Node_t* hashTable[]);

void put(char* key, DATA* data, Node_t* hashTable[]);

Node_t* get(char* key, Node_t* hashTable[]);

void initHashTable(Node_t* hashTable[]);

void deleteList(Node_t* list);

void deleteTable(Node_t* hashTable[]);

void putInt(char* key, int val, Node_t* hashTable[]);

void putString(char* key, const char* str, Node_t* hashTable[]);

void incrementCount(char* key, Node_t* hashTable[]);

int count(Node_t** hashTable);

char** getKeys(Node_t** hashTable);

Node_t* getAll(Node_t* hashTable[]);

Node_t** createTable();

#endif