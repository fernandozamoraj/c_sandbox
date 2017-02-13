#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashtable.h"
#include "debug.h"

/*
   TODO: remove all printf statements
   ----------Hashtable Functions----------------
   Although the data can handle any data type,
   it can only handle int* and char*. If you want to 
   handle other data types simply write some more Functions
   for it.  Copy the function for putInt for example and 
   name putFloat

*/
int getHash(char* str){
  return hash(str) % MAX_SIZE;
}

/*
  http://www.cse.yorku.ca/~oz/hash.html
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

void put(char* key, DATA* data, Node_t* hashTable[]){
  int hashIndex = getHash(key);
  
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

Node_t** createTable(){
  Node_t**  hashTable = malloc(sizeof(Node_t*) * MAX_SIZE);
  
  initHashTable(hashTable);
  
  return hashTable;
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

Node_t* get(char* key, Node_t* hashTable[]){
  int hashIndex = getHash(key);
  
  Node_t* list = hashTable[hashIndex];
  
  //if the hash function works correctly this
  //will always be true because of hash % MAX_SIZE
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

void initHashTable(Node_t* hashTable[]){
  for(int i=0; i<MAX_SIZE; i++){
    hashTable[i] = NULL;
  }
}

void displayTableInt(Node_t* hashTable[]){
  
  printf("\n\n****HASHTABLE INT****");
  for(int i = 0; i < MAX_SIZE; i++){
    Node_t* list = hashTable[i];
    
    if(list != NULL){
      displayListInt(list);
    }
  }
}

void displayTableString(Node_t* hashTable[]){
  
  printf("\n\n****HASHTABLE INT****");
  for(int i = 0; i < MAX_SIZE; i++){
    Node_t* head = hashTable[i];
    
    if(head != NULL){
      displayListString(head);
    }
  }
}

int count(Node_t** hashTable){
  //TODO: walk the entire contents to get count
  return 0;
}

char** getKeys(Node_t** hashTable){
   //TODO get count of every element
   //int keyCount = count(hashTable);
   char** keys = NULL;
   //char** keys = malloc(sizeof(char*)*keyCount);
       
   //TODO: implement a get keys method
   //it will allow for retrieving every value
   //in the hashTable

   //TODO: walk the entire table and retrive keys

   return keys;
}

Node_t* getAll(Node_t* hashTable[]){
  //TODO get all elements
  //1. get the count
  //create a new array with that size 
  //copy all the elements into it 
  //return that array
  Node_t* array = NULL;

  return array;
}


void deleteTable(Node_t* hashTable[]){
  
  DEBUGLOG("\n\n****DELETING HASHTABLE****");
    
  for(int i = 0; i < MAX_SIZE; i++){
    deleteList(hashTable[i]);
  }
  
  DEBUGLOG("\nDeleting hashtable...");
  free(hashTable);
}

