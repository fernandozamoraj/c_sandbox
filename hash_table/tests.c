#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


/*
   ---------TESTS--------------

*/
void testWithInts(){

  DEBUGLOG("\nEntered test with ints");
  fflush(stdin);

   //Create array of Node_t pointers
  Node_t** hashTable = createTableX(7);
  
  printf("\n\nTest with ints....");
  putInt("dog", 1, hashTable);
  putInt("cat", 2, hashTable);
  putInt("horse", 3, hashTable);
  putInt("bird", 4, hashTable);
  putInt("lion", 5, hashTable);
  putInt("tiger", 5, hashTable);
  putInt("zebra", 6, hashTable);
  putInt("dog", 7, hashTable);
  putInt("zebra", 8, hashTable);
  
  //update zebra
  //by updating it's count
  incrementCount("zebra", hashTable);
  
  //notice that gazelle does not exist
  incrementCount("gazelle", hashTable); 
  
  if(get("Rhino", hashTable) == NULL){
    printf("\nRhino test PASSED..");
  }
  
  displayTableInt(hashTable);
  deleteTable(hashTable);
}

void testWithWords(){
  char* words[] = 
          {"the",    "cat",    "was",    "from",  "a",   "planet", 
           "called", "mars",   "and",    "pluto", "was", "from", 
           "a",      "planet", "called", "pluto"};
  Node_t** hashTable = createTable();
  
  printf("\n\n******TEST WITH WORDS**********");
  for(int i=0;i<16;i++){
    incrementCount(words[i], hashTable);
  }
  
  displayTableInt(hashTable);
  
  deleteTable(hashTable);
                   
  printf("\n\n******END OF TEST WITH WORDS**********");                 
}

void testWithStrings(){
   //Create array of Node_t pointers
  Node_t**  hashTable = createTable();
  
  printf("\n\nTest with strings....");
  putString("dog", "bone", hashTable);
  putString("cat", "toy", hashTable);
  putString("horse", "hay", hashTable);
  putString("bird", "feed", hashTable);
  putString("cat", "yarn", hashTable); //for collision
  
  Node_t* item = get("bird", hashTable);

  displayTableString(hashTable);
  deleteTable(hashTable);
}

void displayMyString(char* key, DATA* data){
    char* stringData = data;
    printf("\nkey: %s data: %s", key, stringData);
}

void displayMyInt(char* key, DATA* data){
    int* intData = data;
    printf("\nkey: %s data: %d", key, *intData);
}

void testWithFunctionPointer(){
     //Create array of Node_t pointers
  Node_t**  hashTable = createTable();
  
  printf("\n\n***TEST WITH FUNCTION POINTER*****");
  putString("shoe", "sock", hashTable);
  putString("shirt", "tie", hashTable);
  putString("pants", "belt", hashTable);
  
  displayTable(&displayMyString, hashTable);
  deleteTable(hashTable);
  printf("\n\n****END TEST WITH FUNCTION POINTER***");
}

void testWithFunctionPointerInt(){
     //Create array of Node_t pointers
  Node_t**  hashTable = createTable();
  
  printf("\n\n***TEST WITH FUNCTION POINTER*****");
  putInt("shoe", 1, hashTable);
  putInt("shirt", 2, hashTable);
  putInt("pants", 3, hashTable);
  
  displayTable(&displayMyInt, hashTable);
  deleteTable(hashTable);
  printf("\n\n****END TEST WITH FUNCTION POINTER***");
}

void testCountFunction(){
    Node_t**  hashTable = createTable();
  
  printf("\n\n***TEST COUNT TABLE*****");
  putInt("shoe", 1, hashTable);
  putInt("shirt", 2, hashTable);
  putInt("pants", 3, hashTable);

  printf("\nTable Item Count: %d", countTable(hashTable));

  deleteTable(hashTable);

}

void testGetKeys(){
    Node_t**  hashTable = createTable();
  
  printf("\n\n***TEST GET KEYS*****");
  putInt("shoe", 1, hashTable);
  putInt("shirt", 2, hashTable);
  putInt("pants", 3, hashTable);

  printf("\nTable Item Count: %d", countTable(hashTable));

  char** keys = getKeys(hashTable);
  int i = 0;
  while(keys[i]){
    printf("\nkeys[%d] is %s", i, keys[i]);
    i++;
  }
  freeKeys(keys);
  deleteTable(hashTable);

}

void testGetAll(){
  int i = 0;
  char* words[] = {"the", "cat", "was", "from", "a", "planet", "called", 
                   "mars", "and", "pluto", "was", "from", "a", "planet", 
                   "called", "pluto"};

  Node_t** hashTable = createTableX(10);
  
  printf("\n\n******TEST GET ALL**********");
  for(i=0;i<16;i++){
    incrementCount(words[i], hashTable);
  }
  
  Node_t** all = getAll(hashTable);
  DEBUGLOG("\n********GOT ALL**************");
  
  i = 0;
  while(all[i] != NULL){

    int* value = all[i]->data;
    printf("\nKey: %s Value: %d", all[i]->key, *value);
    i++;
  }
  DEBUGLOG("\n************exited while***********");

  //There is no need to free all
  //TODO: on second thought there is a need to free all node pointers

  deleteTable(hashTable);
                   
  printf("\n\n******END OF TEST GET ALL**********");                 
}


void testGetValue(){
  int i = 0;
  char* words[] = {"the", "cat", "was", "from", "a", "planet", "called", "cat"};
  Node_t** hashTable = createTableX(10);
  
  printf("\n\n******TEST GET VALUE**********");
  for(i=0;i<8;i++){
    incrementCount(words[i], hashTable);
  }
  
  printf("\n\n\n    VALUES   \n");
  for(i=0;i<7;i++){
    int* value = getValue(words[i], hashTable);
    if(value != NULL){
      printf("\nKey: %20s Value: %3d", words[i], *value);
    }
  }

  deleteTable(hashTable);
                   
  printf("\n\n******END OF TEST GET VALUE**********");                 
}

int main(void) {
  
  DEBUGLOG("\n****Start of main****");

  /*
  testWithInts();
  testWithStrings();
  testWithWords();
  testWithFunctionPointer();
  testWithFunctionPointerInt();
  testCountFunction();
  testGetKeys();
  testGetAll();
  */

  testGetValue();
  
  return 0;
}
