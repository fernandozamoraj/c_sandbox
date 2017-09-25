#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashtable.h"
#include "debug.h"



/*

   ----------Hashtable Functions----------------
   Although the data can handle any data type,
   it can only handle int* and char*. To 
   handle other data types more data type specific 
   functions are necessary.  
   Copy the function for putInt for example and 
   name putFloat and implement to handle float.

   As an alternative function pointers can be used. 
   The API user would then have to define their type
   specific functions.


*/
int getHash(char* str, int tableSize){
  //members prior to FIRST_ALLOWABLE_INDEX are for metadata
  return (hash(str) % tableSize)+ FIRST_ALLOWABLE_INDEX;  
}

int getTableSize(Node_t* hashTable[]){
  int *s = hashTable[0]->data;

  return *s;
}

/*
  hashing algorithm take from link below
  http://www.cse.yorku.ca/~oz/hash.html

  Hashing explained in wikipedia link below.
  https://en.wikipedia.org/wiki/Hash_table

*/
unsigned long hash(unsigned char* str){
  unsigned long hash = 5381;
  int c;
  
  while(c = *str++){
    hash = ((hash << 5) + hash) + c;
  }
  
  return hash;
}

Node_t** createTable(){
  return createTableX(MAX_TABLE_SIZE);
}

Node_t** createTableX(int size){
  Node_t**  hashTable = malloc(sizeof(Node_t*) * (size + 1)); //one extra for special size node
  
  DEBUGLOG("\n*****ALLOCATED hashTable********");
  initHashTable(hashTable, size);
  DEBUGLOG("\n*****INITIALIZED hashTable********");
  

  //Keep this in mind to allow more dynamic sizing
  //index zero is for storing metadata
  int* tableSize = malloc(sizeof(int));
  
  *tableSize = size;
  char* metadata = "metadata";
  hashTable[0] = createLink();
  hashTable[0]->key = strdup(metadata);
  hashTable[0]->data = tableSize;
  DEBUGLOG("\n*****Created metad data********");
  
  return hashTable;
}

/*
*
*/
void put(char* key, DATA* data, Node_t* hashTable[]){
  int hashIndex = getHash(key, getTableSize(hashTable));
  
  Node_t* list = hashTable[hashIndex];
  
  DEBUGLOG("\nPutting %s at %d", key, hashIndex);
  
  if(list == NULL){
    hashTable[hashIndex] = createLink();
    hashTable[hashIndex]->key = strdup(key);
    hashTable[hashIndex]->data = data;
  }
  else{  //collision
    
    DEBUGLOG("\nFound collision with %s", key);
    
    Node_t* node = findNode(key, list);
    
    if(node == NULL){
      
      DEBUGLOG("\nAdding node for %s", key);
      node = addNode(key, data, list);
    }
    else{

      //free the node data since it is being replaced with new
      //allocated data and simply update the data 
      free(node->data);
      node->data = data;
    }
  }
}

void putInt(char* key, int val, Node_t* hashTable[]){
  
  int* newVal = malloc(sizeof(val));
  *newVal = val;
  
  put(key, newVal, hashTable);
}

void putString(char* key, const char* str, Node_t* hashTable[]){
  char* newVal = strdup(str);
  put(key, newVal, hashTable);
}

/**
*    This function assumes key-value of char*-int.
*    You can keep passing a word to it an it increments
*    the number associated with that word.
*    If the word is not already in the table it adds it
*    with an initial value of 1 for the count.
*
*/
void incrementCount(char* key, Node_t* hashTable[]){
   Node_t* node = get(key, hashTable);
  
  if(node != NULL){
    int* val = node->data;
    putInt(key, ++(*val), hashTable);
  }
  else{
    putInt(key, 1, hashTable);
  }
}

/**
*     get returns a pointer to the Node_t struc if
*     it finds the associated key, NULL otherwise.
**/
Node_t* get(char* key, Node_t* hashTable[]){
  int hashIndex = getHash(key, getTableSize(hashTable));
  
  Node_t* list = hashTable[hashIndex];
  
  if(list != NULL){  
    
    Node_t* node = findNode(key, list);
    
    if(node == NULL){
      DEBUGLOG("\n%s not found: ", key);
      return NULL;
    }
    else{
      DEBUGLOG("\nFound %s at %d", key, hashIndex);
      return node;
    }
  }
  
  return NULL;
}


DATA* getValue(char* key, Node_t* hashTable[]){
  Node_t* dataNode = get(key, hashTable);

  if(dataNode != NULL){
    return dataNode->data;
  }

  return NULL;
}

/**
*  inits all pointers in the hasTable to NULL
*/
void initHashTable(Node_t* hashTable[], int size){

  for(int i=FIRST_ALLOWABLE_INDEX; i <= size; i++){
    hashTable[i] = NULL;
  }
}

/**
*   displayTableInt - displays the values of the table
*   when the data in each node is of type in.
*   Requires linked list functionality
*/
void displayTableInt(Node_t* hashTable[]){
  
  int size = getTableSize(hashTable);
  printf("\n\n****HASHTABLE INT****");
  for(int i = FIRST_ALLOWABLE_INDEX; i <= size; i++){
    Node_t* list = hashTable[i];
    
    if(list != NULL){
      displayListInt(list);
    }
  }
}

void displayTableString(Node_t* hashTable[]){
  
  int size = getTableSize(hashTable);
  printf("\n\n****HASHTABLE INT****");
  for(int i = FIRST_ALLOWABLE_INDEX; i <= size; i++){
    Node_t* head = hashTable[i];
    
    if(head != NULL){
      displayListString(head);
    }
  }
}


void displayTable(void (*displayFunc)(char*, DATA*), Node_t* hashTable[]){

  int size = getTableSize(hashTable);
  printf("\n\n****HASHTABLE INT****");
  for(int i = FIRST_ALLOWABLE_INDEX; i <= size; i++){
    Node_t* head = hashTable[i];
    
    if(head != NULL){
      displayList(displayFunc, head);
    }
  }
}


int countTable(Node_t** hashTable){
  int count = 0;
  int tempCount = 0;

  int size = getTableSize(hashTable);

  for(int i=FIRST_ALLOWABLE_INDEX; i <= size; i++){
    tempCount = countList(hashTable[i]);
    count += tempCount;
  }

  DEBUGLOG("\nTable count: %d", count);

  return count;
}

char** getKeys(Node_t** hashTable){
   DEBUGLOG("\nentered getKeys");
   //TODO get count of every element
   //int keyCount = count(hashTable);
   //char** keys = NULL;
   int count = countTable(hashTable);
   DEBUGLOG("\nGot count of %d", count);
   char** keys = malloc(sizeof(char*) * (count + 1));
   int j = 0;
   int size = getTableSize(hashTable);

   for(int i = FIRST_ALLOWABLE_INDEX; i <= size; i++ ){

     Node_t* list = hashTable[i];
     while(list != NULL){
        DEBUGLOG("\nValue %s", list->key);

        keys[j] = strdup(list->key);
        j++;
        list = list->next;
     }
   }
   keys[j] = NULL;

   return keys;
}

void freeKeys(char** keys){
  int i = 0;
  while(keys[i] != NULL){
    free(keys[i]);
    i++;
  }

  free(keys);
}

Node_t** getAll(Node_t* hashTable[]){
   DEBUGLOG("\n**********Entered getAll***********");
   int nodeCount = countTable(hashTable);
   DEBUGLOG("\n**********Got Count***********");
   

   int size = getTableSize(hashTable);
  DEBUGLOG("\n**********Got Table Size***********");
   
   Node_t** myArray = NULL;
   
   if(nodeCount > 0){
      myArray = malloc(sizeof(Node_t*) * (nodeCount+1));
   }
   DEBUGLOG("\n**********ALLOCATED SIZE Size: %d***********", nodeCount);
   

   int j = 0;
   for(int i=FIRST_ALLOWABLE_INDEX;i<=size;i++){
     DEBUGLOG("\n**********LOOPING %d***********", i);
     Node_t* list = hashTable[i];
     while(list != NULL){
        DEBUGLOG("\n**********WALKING LIST %s***********", list->key);
        myArray[j] = list;
        list = list->next;
        j++;
     }
   }

   DEBUGLOG("\n***********exited loop*************");
   if(j > 0){
     myArray[j] = NULL;
   }
   DEBUGLOG("\n***********ASSINED NULL TO*************");


   return myArray;
}


void deleteTable(Node_t* hashTable[]){
  
  int size = getTableSize(hashTable);
  DEBUGLOG("\n\n****DELETING HASHTABLE****");
    
  //This deletes from zero to also clear out metadata node 0  
  for(int i = 0; i <= size; i++){
    deleteList(hashTable[i]);
  }
  
  DEBUGLOG("\nDeleting hashtable...");
  free(hashTable);
}

