#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


/*
   ---------TESTS--------------

*/

void testWithInts();
void testWithWords();
void testWithStrings();

char* getNextWord(char* word, FILE* fp){
    /*get next word magic here*/
    return word;   
}
void readFileExample(char* fileName, Node_t* hashTable[]){

    /*
    char* word;
    FILE* fp = fopen(file, "r");

    while((word = getNextWord(fp)) != NULL){
       incrementCount(word, hashTable);
       free(word);
    }

    //this can wait if reading multiple files
    displayTableInt(hashtable);

    fclose(fp);
    */
}

int main(void) {
  
  printf("\n\n***********BEGIN ALL TESTS*********");

  testWithInts();
  testWithStrings();
  testWithWords();

  printf("\n\n***********END OF ALL TESTS*********");

  return 0;
}

void testWithInts(){
   //Create array of Node_t pointers
  Node_t** hashTable = createTable();
  
  printf("\n\n********TEST WITH INTS***********");
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

  printf("\n\n************END OF TEST WITH INTS********");
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
  
  printf("\n\n******TEST WITH STRINGS**********");

  putString("dog", "bone", hashTable);
  putString("cat", "toy", hashTable);
  putString("horse", "hay", hashTable);
  putString("bird", "feed", hashTable);
  putString("cat", "yarn", hashTable); //for collision
  
  Node_t* item = get("bird", hashTable);

  displayTableString(hashTable);
  deleteTable(hashTable);

  printf("\n\n******END OF TEST WITH STRINGS**********");
}


