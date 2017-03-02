#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX_WORD_SIZE 256

/*
    Index 0 of the table is reserved for meta-data.
    Things like list size, node count, thresholds and such
    can are stored in element 0 of the table.
    All other data elements begin at FIRST_ALLOWABLE_INDEX.
    Decided not to use global variables because they would
    be affected when more than one table exists.
    A different solution could be to create a container struct
    that holds the inner table.
    This works fine since the table holds any data type.

*/
#define FIRST_ALLOWABLE_INDEX 1

/*
    COLLISION_THRESHOLD is the maximum number of collisions
    in the table that triggers in the bucket. When that number
    is reached in any bucket a resize is triggered.
*/
#define COLLISION_THRESHOLD 5

/*
     NEW_SIZE_FACTOR is the multiplier by which the number of
     actual nodes in the table is multiplied by when re-sizing
     the table.
*/
#define NEW_SIZE_FACTOR 3

#define HIGHEST_COLLISION_COUNT_STR "highest_collision_count"

#define NODE_COUNT_STR "node_count"

#define TABLE_SIZE_STR "table_size"

/*
*   Change this size to a lower value like 5
*   and turn on DEBUG to watch collisions happen.
*   This value is only used when not not specifying
*   the table size.
*/
#define MAX_TABLE_SIZE 1000
#define DATA void

/*
*    Remove this line or change to DEBUGOFF
*    to print DEBUG statements
*/
#define DEBUGOFF

/*
* Macro for printing debug statements
* It is called just like the printf statement.
*/
#ifdef DEBUG
#define DEBUGLOG(ARGS...) printf(ARGS)
#else
#define DEBUGLOG(ARGS...) do{}while(0)
#endif

/*
*  getNextWord - Gets the next word in the file.
*/
char *getNextWord(FILE *fd);

/*
*  Node - holds the data in the list and pointer to next
*
*  In reality this shouldbe separate from Node
*  key and data should be in a KeyValue pair
*  and a node should contain that as nested struct
*/
typedef struct Node{
  char* key;
  DATA* data;
  struct Node* next;
} Node_t;

/*******************************************
*
*             List Functions
*
********************************************/

/*
*   createLink - dynamically allocates memory for a Node_t type
*   creates a type of Node_t* and returns it
*/
Node_t* createLink();

/*
*   findNode - Finds the node for the given key
*/
Node_t* findNode(char* key, Node_t* list);

/*
*   addNode - Adds a node for the given key with the given data
*/
Node_t* addNode(char* key, DATA* data, Node_t* list);

/*
*  getTail - Gets the last node in the list.  It returns a node
*  unless the list is emtpy
*/
Node_t* getTail(Node_t* list);

/*
*  deleteList - Deletes all dynamically allocated data in the table.
*  Deletes the key, data and each node within the
*  the list, to include the list.
*/
void deleteList(Node_t* list);

/*
*  displayListInt - Displays the list as integers if the data holds ints
*  This can better be change to be dynamic by passign a
*  function pointer to display the list of whatever type.
*/
void displayListInt(Node_t* list);

/*
*  Displays the list as strings if the data holds ints
*  This can better be change to be dynamic by passign a
*  function pointer to display the list of whatever type
*/
void displayListString(Node_t* list);

/*
*   displayList - Displays list for any data type.
*   displayFunc - is a user defined function
*
*/
void displayList(void (*displayFunc)(char*, DATA*), Node_t* list);

/*
*  countList - counts the nodes in the list
*  can be quite slow since it walks the list.
*  A better option would be to just keep track of the count.
*/
int countList(Node_t* list);


/********************************************
*
*      HASHTABLE FUNCTIONS
*
**********************************************/

/*
*  hash - High speed algorithm taken from online to hash
*/
unsigned long hash(unsigned char* str);

/*
*  getHash - Uses hash algorithm and mods it by MAX_TABLE_SIZE
*/
int getHash(char* str, int tableSize);

/*
* Gets the table size
*/
int getTableSize(Node_t* hashTable[]);

/*
*  displayTableInt - Displays the table values when data stored is int*
*/
void displayTableInt(Node_t* hashTable[]);

/*
*  displayTableString - Displays the table values when data stored is char*
*/
void displayTableString(Node_t* hashTable[]);

/*
*    this function requires a function pointer to print
*    exampe: declare a function like this.
*    Requires user defined function due to void* pointer
*
*    void printMyData(char* key, DATA* data){
*        char* stringData = data;
*        printf("key: %s data: %s", key, stringData);
*    }
*
*    and call it as
*    displayTable(&printData, hashTable);
*/
void displayTable(void (*displayFunc)(char*, DATA*), Node_t* hashTable[]);

/*
*  put - Puts a value into the table with the value in key and data.
*  If the value exists it overwrites the data. If it does not
*  it creates an entry.
*/
Node_t** put(char* key, DATA* data, Node_t* hashTable[], int resize, int dupkey);

/*
*  get - Gets an element by it's key
*  Returns Node_t* for the value found.
*  Returns NULL if key not found
*/
Node_t* get(char* key, Node_t* hashTable[]);

/*
*  getValue - Gets the value from the hashtable with the given key
*/
DATA* getValue(char* key, Node_t* hashTable[]);

/*
*  Initializes the hashTable to NULL pointers
*/
void initHashTable(Node_t* hashTable[], int size);

/*
*   deleteTable - frees every node in the table to include the table
*/
void deleteTable(Node_t* hashTable[]);

/*
*  Wrapper for put to put int values into the data
*/
Node_t** putInt(char* key, int val, Node_t* hashTable[]);

/*
*  Wrapper for put to put char* (C Strings) into the data
*/
Node_t** putString(char* key, const char* str, Node_t* hashTable[]);

/*
*   Easy API for creating a hashTable of counts. Key-value pairs must
*   be char*-int* pairs for this to work.
*/
Node_t** incrementCount(char* key, Node_t* hashTable[]);

/*
*   count - Gets count of all NON-NULL items in the table
*/
int countTable(Node_t** hashTable);

/*
*   getKeys - Gets an array of char strings for all keys in table
*/
char** getKeys(Node_t** hashTable);

/*
*   freeKeys - Frees the keys. It must be called after get keys
*/
void freeKeys(char** keys);

/*
*   getAll - returns an array of nodes in the hashTable
*   returns an array of all non-NULL nodes in the table.
*   It returns one extra element at the end that is NULL
*   to help identify the end of the the array.
*/
Node_t** getAll(Node_t* hashTable[]);

/*
*  createTable - creates hashTable and returns it as Node_t** which can be
*  accessed as Node_t* table[]
*/
Node_t** createTable();

/*
*  createTableX - Creates a table of a given size
*/
Node_t** createTableX(int size);

/*
*  Updates the table count.  The count is used when it
*  and only if it is greater than the existing highest
*  collision value.
*/
void updateCollisionCount(int count, Node_t* hashTable[]);

/*
*  updateCount - updates the count of non-NULL nodes in table
*/
void updateNodeCount(Node_t* hashTable[]);

int getNodeCount(Node_t* hashTable[]);

int getHighestCollision(Node_t* hashTable[]);

#endif
