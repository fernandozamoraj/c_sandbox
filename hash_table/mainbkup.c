#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


/*
   ---------TESTS--------------

*/
void testWithInts(){
   //Create array of Node_t pointers
  Node_t** hashTable = createTable();
  
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
  char* words[] = {"the", "cat", "was", "from", "a", "planet", "called", "mars", "and", 
                   "pluto", "was", "from", "a", "planet", "called", "pluto"};
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

void testWithFunctionPointer(void (*printGeneric)(char*, DATA*)){
     //Create array of Node_t pointers
  Node_t**  hashTable = createTable();
  
  printf("\n\n***TEST WITH FUNCTION POINTER*****");
  putString("shoe", "sock", hashTable);
  putString("shirt", "tie", hashTable);
  putString("pants", "belt", hashTable);
  
  displayTable(printGeneric, hashTable);
  deleteTable(hashTable);
  printf("\n\n****END TEST WITH FUNCTION POINTER***");
}

void displayMyString(char* key, DATA* data){
    char* stringData = data;
    printf("\nkey: %s data: %s", key, stringData);
}

int main(void) {
  
  testWithInts();
  testWithStrings();
  testWithWords();
  testWithFunctionPointer(&displayMyString);
  
  return 0;
}
