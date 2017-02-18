#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "consts.h"
#include "debug.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define FIRST_ALLOWABLE_INDEX 1

/*
    -----------Hashtable functions----------------
*/


/*
* High speed algorithm take from online to hash
*/
unsigned long hash(unsigned char* str);

/*
* Uses hash algorithm and mods it by MAX_TABLE_SIZE
*/
int getHash(char* str, int tableSize);

int getTableSize(Node_t* hashTable[]);
/*
* Displays the table values when data stored is int*
*/
void displayTableInt(Node_t* hashTable[]);

/*
* Displays the table values when data stored is char*
*/
void displayTableString(Node_t* hashTable[]);

/*
    this function requires a function pointer to print
    exampe: declare a function like this
    void printMyData(char* key, DATA* data){
        char* stringData = data;
        printf("key: %s data: %s", key, stringData);
    }

    and call it as 
    displayTable(&printData, hashTable);
*/
void displayTable(void (*displayFunc)(char*, DATA*), Node_t* hashTable[]);

/*
* Puts a value into the table with the value in key and data.
* If the value exists it overwrites the data. If it does not
* it creates an entry.
*/
void put(char* key, DATA* data, Node_t* hashTable[]);

/*
* Gets an element by it's key
* Returns Node_t* for the value found.
*  Returns NULL if key not found
*/
Node_t* get(char* key, Node_t* hashTable[]);

DATA* getValue(char* key, Node_t* hashTable[]);

/*
*  Initializes the hashTable to NULL pointers
*/
void initHashTable(Node_t* hashTable[], int size);



/*
* deleteTable deletes frees every node in the table to include the table
*/
void deleteTable(Node_t* hashTable[]);

/*
*  Wrapper for put to put int values into the data
*/
void putInt(char* key, int val, Node_t* hashTable[]);

/*
* Wrapper for put to put char* (C Strings) into the data
*/
void putString(char* key, const char* str, Node_t* hashTable[]);

/*
* Easy API for creating a hashTable of counts. Key-value pairs must 
* be char*-int* pairs for this to work.
*/
void incrementCount(char* key, Node_t* hashTable[]);

/*
* count - Gets count of all NON-NULL items in the table
*/
int countTable(Node_t** hashTable);

/*
* getKeys - Gets an array of char strings for all keys in table
*/
char** getKeys(Node_t** hashTable);
void freeKeys(char** keys);

/*
* getAll - returns an array of nodes in the hashTable
*/
Node_t** getAll(Node_t* hashTable[]);

/*
*  creates hashTable and returns it as Node_t** which can be
*  accessed as Node_t* table[]
*/
Node_t** createTable();
Node_t** createTableX(int size);

#endif