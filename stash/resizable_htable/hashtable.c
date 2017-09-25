#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"


char *getNextWord(FILE *fd)
{
	int index = 0;
	int charValue;
	char word[MAX_WORD_SIZE];

	while((charValue = fgetc(fd)) != EOF)
	{
		if(isspace(charValue))
		{
			word[index] = '\0';

			return (char *)strdup(word);
		}

		else if(((index + 1) != (MAX_WORD_SIZE - 1)) && (isalnum(charValue)))
		{

			charValue = tolower(charValue);
			word[index] = charValue;
		}

		else
		{
			word[index] = '\0';
			return (char *)strdup(word);
		}

		index++;
	}

	return NULL;
}

/*
  -------List functions----------

*/
Node_t* createLink(){
  Node_t* newLink = malloc(sizeof(Node_t));

  if(newLink != NULL){
    newLink->next = NULL;
    newLink->data = NULL;
  }

  return newLink;
}

Node_t* findNode(char* key, Node_t* list){

  Node_t* temp = list;

  while(temp != NULL){
    if(strcmp(key, temp->key) == 0){
      return temp;
    }
    temp = temp->next;
  }

  return temp;
}

Node_t* addNode(char* key, DATA* data, Node_t* list){
  Node_t* node = createLink();
  Node_t* tail = NULL;

  node->key = strdup(key);
  node->data = data;

  tail = getTail(list);
  tail->next = node;

  return node;
}

Node_t* getTail(Node_t* list){

  Node_t* temp = list;
  Node_t* tail = list;

  if(temp != NULL){
    while(tail->next != NULL){
      tail = tail->next;
    }
  }

  return tail;
}

void displayListInt(Node_t* list){
  Node_t* temp = list;
  int *value = 0;

  while(temp != NULL){
    value = temp->data;
    printf("\n%d %s", *value, temp->key);
    temp = temp->next;
  }
}

void displayListString(Node_t* list){
  Node_t* temp = list;
  char *value;

  while(temp != NULL){
    value = temp->data;
    printf("\n%s %s", value, temp->key);
    temp = temp->next;
  }
}

void displayList(void (*displayFunc)(char*, DATA*), Node_t* list){
  Node_t* temp = list;

  while(temp != NULL){
    (*displayFunc)(temp->key, temp->data);
    temp = temp->next;
  }
}

void deleteList(Node_t* list){

  Node_t* temp = list;
  Node_t* next = list;

  while(temp != NULL){
    next = temp->next;

    DEBUGLOG("\nDeleting %s...", temp->key);

    //Key and data are dynamic so they must
    //be freed.
    free(temp->key);
    free(temp->data);
    free(temp);

    temp = next;
  }
}

int countList(Node_t* list){
  Node_t* temp = list;
  int count = 0;

  while(temp != NULL){
    temp = temp->next;
    count++;
  }

  return count;
}


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

/*
*  getTableSize - gets the table size from the metadata node
*/
int getTableSize(Node_t* hashTable[]){
  int *s = hashTable[0]->data;

  return *s;
}

int getHighestCollision(Node_t* hashTable[]){
  //TODO: use define for highest collision
  Node_t *node = findNode(HIGHEST_COLLISION_COUNT_STR, hashTable[0]);

  if(node != NULL){
    int *highestCollision = node->data;
    return *highestCollision;
  }

  return 1;
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



/*


*/
Node_t** resizeTable(Node_t** hashTable){

    int highestCollision = getHighestCollision(hashTable);

    DEBUGLOG("\nHighestCollision: %d", highestCollision);
    if(highestCollision < COLLISION_THRESHOLD){
      DEBUGLOG("\nNot resizing...");
      return hashTable;
    }
    DEBUGLOG("\nResizing....");

    int nodeCount = countTable(hashTable);

    Node_t** newTable = createTableX(nodeCount * NEW_SIZE_FACTOR);

    Node_t** allNodesTable = getAll(hashTable);

    /* disconnect all lists*/
    int i = 0;
    while(allNodesTable[i]){

        put(allNodesTable[i]->key, allNodesTable[i]->data, newTable, 0, 0);
        i++;
    }

    int oldTableSize = getTableSize(hashTable);

    for(i=0;i<oldTableSize;i++){
        Node_t* list = hashTable[i];

        Node_t* temp = list;
        Node_t* previous;

        /*
        *  We only free the nodes but not the data because
        *  we are still referencing the data the new tables
        */
        while(temp != NULL){
            previous = temp->next;
            free(temp);
            temp = previous;
        }
    }

    free(hashTable);
    free(allNodesTable);

    return newTable;
}

/*
     Creates the table dynamically
*/
Node_t** createTable(){
  return createTableX(MAX_TABLE_SIZE);
}

/*
   Allows a resizeable table

*/
Node_t** createTableX(int size){
  Node_t**  hashTable = malloc(sizeof(Node_t*) * (size + 1)); //one extra for special size node

  DEBUGLOG("\n*****ALLOCATED hashTable********");
  initHashTable(hashTable, size);
  DEBUGLOG("\n*****INITIALIZED hashTable********");


  //Keep this in mind to allow more dynamic sizing
  //index zero is for storing metadata
  int* tableSize = malloc(sizeof(int));

  *tableSize = size;
  char* metadata = TABLE_SIZE_STR;
  hashTable[0] = createLink();
  hashTable[0]->key = strdup(metadata);
  hashTable[0]->data = tableSize;

  /* store the count in the second link of the zero element */
  int* nodeCount = malloc(sizeof(int));
  *nodeCount = 0;
  addNode(NODE_COUNT_STR, nodeCount, hashTable[0]);

  /* store the highest collision*/
  int* highestCollision = malloc(sizeof(int));
  *highestCollision = 0;
  addNode(HIGHEST_COLLISION_COUNT_STR, highestCollision, hashTable[0]);

  DEBUGLOG("\n*****Created meta data********");

  return hashTable;
}

void updateCollisionCount(int count, Node_t* hashTable[]){
    Node_t* node = findNode(HIGHEST_COLLISION_COUNT_STR, hashTable[0]);

    if(node != NULL){
      int* highestCount = node->data;

      if(*highestCount < count){
        DEBUGLOG("\nHighest Collision Updated: %d", count);
        *((int*)node->data) = count;
      }
    }
}

void updateNodeCount(Node_t* hashTable[]){
    Node_t* node = findNode(NODE_COUNT_STR, hashTable[0]);

    if(node != NULL){
        int *count = node->data;
        *count = *count + 1;
        DEBUGLOG("\nNode count updated: %d", count);
        *((int*)node->data) = *count;
    }
}

int getNodeCount(Node_t* hashTable[]){
    Node_t* node = findNode(NODE_COUNT_STR, hashTable[0]);

    if(node != NULL){
        int *count = node->data;

        return *count;
    }

    return 1;
}

/*
  put - places a key value pair into the table.
*/
Node_t** put(char* key, DATA* data, Node_t* hashTable[], int resize, int dupkey){
  int hashIndex = getHash(key, getTableSize(hashTable));

  Node_t* list = hashTable[hashIndex];
  int addedNode = 1;    /*default to true for adding new node*/

  DEBUGLOG("\nPutting %s at %d", key, hashIndex);

  if(list == NULL){
    hashTable[hashIndex] = createLink();

    /*
       This becomes important when copying the data from another table.
       When copying data from another table you may not want to dupe the key.
    */
    if(dupkey){
        hashTable[hashIndex]->key = strdup(key);
    }
    else{
        hashTable[hashIndex]->key = key;
    }

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
      addedNode = 0;
    }

    int count = countList(list);

    DEBUGLOG("\ncount: %d", count);
    updateCollisionCount(count, hashTable);

    if(resize){
        hashTable = resizeTable(hashTable);
    }
  }

  if(addedNode){
    updateNodeCount(hashTable);
  }

  return hashTable;
}

Node_t** putInt(char* key, int val, Node_t* hashTable[]){

  int* newVal = malloc(sizeof(val));
  *newVal = val;

  return put(key, newVal, hashTable, 1, 1);
}

Node_t** putString(char* key, const char* str, Node_t* hashTable[]){
  char* newVal = strdup(str);
  return put(key, newVal, hashTable, 1, 1);
}

/**
*    This function assumes key-value of char*-int.
*    You can keep passing a word to it an it increments
*    the number associated with that word.
*    If the word is not already in the table it adds it
*    with an initial value of 1 for the count.
*
*/
Node_t** incrementCount(char* key, Node_t* hashTable[]){
   Node_t* node = get(key, hashTable);

  if(node != NULL){
    int* val = node->data;
    return putInt(key, ++(*val), hashTable);
  }
  else{
    return putInt(key, 1, hashTable);
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
  DEBUGLOG("\n\n****HASHTABLE INT****");
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

  return getNodeCount(hashTable);
}

char** getKeys(Node_t** hashTable){
   DEBUGLOG("\nentered getKeys");

   /*
   *   count is different than size
   *   Count is the actual number non NULL nodes
   *   in the table.
   *   Size is the number of buckets in the table
   */
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

   //allocates one extra node to have a NULL marker at end of list
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
     /*
        Mark last node in the array NULL
        This serves as a marker for the end of the
        array.
     */
     myArray[j] = NULL;  //
   }
   DEBUGLOG("\n***********ASSIGNED NULL TO*************");


   return myArray;
}


void deleteTable(Node_t* hashTable[]){

  DEBUGLOG("\n\n****DELETING HASHTABLE****");

  for(int i = 0; i < MAX_TABLE_SIZE; i++){
    deleteList(hashTable[i]);
  }

  DEBUGLOG("\nDeleting hashtable...");
  free(hashTable);
}

