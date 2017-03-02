#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"



char *getNextWord(FILE *fd){
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

/***********************************************
*
*             List functions
*
*************************************************/

Node_t* addNode(char* key, DATA* data, Node_t* list){
  Node_t* node = createLink();
  Node_t* tail = NULL;

  strcpy(node->key, key);
  node->data = data;

  tail = getTail(list);
  tail->next = node;

  return node;
}

Node_t* createLink(){
  Node_t* newLink = malloc(sizeof(Node_t));

  if(newLink != NULL){
    newLink->next = NULL;
    newLink->data = NULL;
  }
  else{
    printf("\n!!!!!Unable to allocate memory for new link!!!!!!");
  }

  return newLink;
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

void deleteList(Node_t* list){

  Node_t* temp = list;
  Node_t* next = list;

  while(temp != NULL){
    next = temp->next;

    DEBUGLOG("\nDeleting %s...", temp->key);

    //Key is dynamic so they must
    //be freed.
    free(temp->data);
    free(temp);

    temp = next;
  }
}

void displayList(void (*displayFunc)(char*, DATA*), Node_t* list){
  Node_t* temp = list;

  while(temp != NULL){
    (*displayFunc)(temp->key, temp->data);
    temp = temp->next;
  }
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

Node_t* findNode(char* key, Node_t* list){

  Node_t* temp = list;

  while(temp != NULL){
    if(strcmp(key, temp->key) == 0){
      return temp;
    }
    temp = temp->next;
  }

  return NULL;
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


/******************************************************
*
*   ----------Hashtable Functions----------------
*   Although the data can handle any data type,
*   it can only handle int* and char*. To
*   handle other data types more data type specific
*   functions are necessary.
*   Copy the function for putInt for example and
*   name putFloat and implement to handle float.
*
*   As an alternative function pointers can be used.
*   The API user would then have to define their type
*   specific functions.
*
********************************************************/


/*
*     Creates the table using the default value
*     in MAX_TABLE_SIZE
*     This method was left behind from previous task
*     to maintain backwards compatibility.
*
*/
Node_t** createTable(){
  return createTableX(MAX_TABLE_SIZE);
}

/*
*   Creates a table of the give size paramter.
*   This function does several things.
*   1. It creates table of given size
*   2. It creates the meta-data in the reserved
*      bucket 0.
*      The values stored there are
*      table size - size
*      node count - 0
*      highest collision - 0
*   3. It returns the newly created hashtable
*
*/
Node_t** createTableX(int size){
  Node_t**  hashTable = malloc(sizeof(Node_t*) * (size + 1)); //one extra for special size node

  DEBUGLOG("\n*****ALLOCATED hashTable********");
  initHashTable(hashTable, size+1);
  DEBUGLOG("\n*****INITIALIZED hashTable********");


  //Keep this in mind to allow more dynamic sizing
  //index zero is for storing metadata
  int* tableSize = malloc(sizeof(int));

  *tableSize = size+1;
 
  hashTable[0] = createLink();
  hashTable[0]->data = tableSize;
  strcpy(hashTable[0]->key, TABLE_SIZE_STR);  
  
  /* store the count in the second link of the zero element */
  int* nodeCount = malloc(sizeof(int));
  *nodeCount = 0;
  addNode(NODE_COUNT_STR, nodeCount, hashTable[0]);

  /* store the highest collision*/
  int* highestCollision = malloc(sizeof(int));
  *highestCollision = 0;
  addNode(HIGHEST_COLLISION_COUNT_STR, highestCollision, hashTable[0]);

  DEBUGLOG("\n*****Created metad data********");

  return hashTable;
}

/*
*  it gets the count of the non-NULL values stored
*  in the table.
*/
int countTable(Node_t* hashTable[]){

  return getNodeCount(hashTable);
}

/*
*  frees all memory in the table, buckets, lists, keys
*  and data.
*/
void deleteTable(Node_t* hashTable[]){

  DEBUGLOG("\n\n****DELETING HASHTABLE****");
  int size = getTableSize(hashTable);
  int i = 0;
  
  for(i = 0; i < size; i++){
    deleteList(hashTable[i]);
  }

  DEBUGLOG("\nDeleting hashtable...");
  free(hashTable);
}

/**
*   displayTableInt - displays the values of the table
*   when the data in each node is of type in.
*   Requires linked list functionality
*/
void displayTableInt(Node_t* hashTable[]){

  int size = getTableSize(hashTable);
  DEBUGLOG("\n\n****HASHTABLE INT****");
  int i = 0;
  for(i = FIRST_ALLOWABLE_INDEX; i < size; i++){
    Node_t* list = hashTable[i];

    if(list != NULL){
      displayListInt(list);
    }
  }
}

void displayTableString(Node_t* hashTable[]){

  int size = getTableSize(hashTable);
  printf("\n\n****HASHTABLE INT****");
  int i=0;
  for(i = FIRST_ALLOWABLE_INDEX; i < size; i++){
    Node_t* head = hashTable[i];

    if(head != NULL){
      displayListString(head);
    }
  }
}

/*
*   function to display the table for any data type.
*   The user must define the displayFunc to cast DATA*
*   to their appropriate type.
*/
void displayTable(void (*displayFunc)(char*, DATA*), Node_t* hashTable[]){

  int size = getTableSize(hashTable);
    printf("\n\n****HASHTABLE INT****");
  int i = 0;
  for(i = FIRST_ALLOWABLE_INDEX; i < size; i++){
    Node_t* head = hashTable[i];

    if(head != NULL){
      displayList(displayFunc, head);
    }
  }
}

/*
*  This function must be called after calling getKeys
*/
void freeKeys(char** keys){
  int i = 0;
  while(keys[i] != NULL){
    free(keys[i]);
    i++;
  }

  free(keys);
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

/*
*  This function returns an array of all nodes in the table.
*  It is not a deep copy, meaning that you should not modify
*  the nodes data or next values because it will break the
*  the table. You should free the table it return by calling
*  like below
*  Node_t** all = getAll(hashTable);
*  free(all)
*
*  but you should not free any of the elements it returns.
*/
Node_t** getAll(Node_t* hashTable[]){
   DEBUGLOG("\n**********Entered getAll***********");
   int nodeCount = countTable(hashTable);
   DEBUGLOG("\n**********Got Count***********");


   int size = getTableSize(hashTable);
   DEBUGLOG("\n**********Got Table Size***********");

   Node_t** myArray = NULL;

   //allocates one extra node to have a NULL marker at end of list
   if(nodeCount > 0){
      myArray = malloc(sizeof(Node_t*) * (nodeCount+3));
   }
   DEBUGLOG("\n**********ALLOCATED SIZE Size: %d***********", nodeCount);

   int i =0;
   for(i=0;i<nodeCount+3; i++){
     myArray[i] = NULL;
   }

   int j = 0;
   for(i=FIRST_ALLOWABLE_INDEX;i<size;i++){
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
     myArray[nodeCount] = NULL;  //
   }
   DEBUGLOG("\n***********ASSIGNED NULL TO LAST ELEMENT OF myArray**********");


   return myArray;
}

int getHash(char* str, int tableSize){
  //members prior to FIRST_ALLOWABLE_INDEX are for metadata
  return (hash(str) % (tableSize-1) )+ FIRST_ALLOWABLE_INDEX;
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
   int i = 0;
   for(i = FIRST_ALLOWABLE_INDEX; i < size; i++ ){

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

/*
*  This function looks in the metadata bucket for the node
*  named NODE_COUNT_STR to find the node count.
*  NOTE: bucket element 0 is reserved for metadata
*/
int getNodeCount(Node_t* hashTable[]){
    Node_t* node = findNode(NODE_COUNT_STR, hashTable[0]);

    if(node != NULL){
        int *count = node->data;

        return *count;
    }

    return 1;
}

/*
*  getTableSize - gets the table size from the metadata node
*  This function looks in the first bucket first element
*  of the table for the table size.
*
*  NOTE: Bucket 0 of the table is reserved for metadata.
*  the first node in that bucket stores the table size.
*/
int getTableSize(Node_t* hashTable[]){
  int *s = hashTable[0]->data;

  return *s;
}

/*
*  This function looks in the bucket that corresponds
*  to the given key parameter and returns the data for
*  that node if found.
*  It returns NULL if that key is not found.
*/
DATA* getValue(char* key, Node_t* hashTable[]){
  Node_t* dataNode = get(key, hashTable);

  if(dataNode != NULL){
    return dataNode->data;
  }

  return NULL;
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

/**
*  inits all pointers (buckets) in the hasTable to NULL
*/
void initHashTable(Node_t* hashTable[], int size){
  int i = 0;
  for(i=FIRST_ALLOWABLE_INDEX; i < size; i++){
    hashTable[i] = NULL;
  }
}

/*
  put - places a key value pair into the table.
  This function is long and it does a lot.
  1. It looks to see where to put a key in the table.
  2. If the key exists it replaces it with the new data.
  3. If the key does not exist it creates a brand new node
     and appends it to a bucket.
  4. It also gets the highest collision count as determined
     by the number of nodes in the used bucket.
  5. It updates the collision count if it caused a new higher
     collision count.
  6. It also determines if a brand new node was created. If a
     brand new node was created, it updates the overall count
     of non-NULL nodes in the table.
  7. It calls tableResize if resize parameter is set to 1.
     The resizeTable determines if the density is high enough to
     actually resize.
  8. It returns a pointer to the new table in the case that the
     the table was re-sized.
*/
Node_t** put(char* key, DATA* data, Node_t* hashTable[]){
  int tableSize = getTableSize(hashTable);

  int hashIndex = getHash(key, getTableSize(hashTable));

  //safety mechanism to avoid writing past the end of table
  if(hashIndex >= tableSize ){
    hashIndex = tableSize - 1;
  }

  Node_t* list = hashTable[hashIndex];
  int addedNode = 1;    /*default to true for adding new node*/

  DEBUGLOG("\nPutting %s at %d", key, hashIndex);

  if(list == NULL){
    hashTable[hashIndex] = createLink();

    strcpy(hashTable[hashIndex]->key, key);
    
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

      //if data contains different memory addresses,
      //release the memory
      if(data != node->data){
        free(node->data);
      }
      node->data = data;
      addedNode = 0;
    }

    int count = countList(list);

    DEBUGLOG("\ncount: %d", count);
    updateCollisionCount(count, hashTable);
    hashTable = resizeTable(hashTable);
  }

  if(addedNode){
    updateNodeCount(hashTable);
    DEBUGLOG("\nMade it out of updateNodeCount");
  }

  return hashTable;
}

/*
*  Wrapper function for putting int data into table
*  returns the hashtable.
*  NOTE: Reason that it returns the hash table is in case
*  that the table gets resized. If the table gets resized
*  the memory address will change.
*/
Node_t** putInt(char* key, int val, Node_t* hashTable[]){

  int* newVal = malloc(sizeof(val));
  *newVal = val;

  return put(key, newVal, hashTable);
}

/*
*  Wrapper function for putting char* (C Strings) into
*  data table.
*
*  NOTE: Reason that it returns the hash table is in case
*  that the table gets resized. If the table gets resized
*  the memory address will change.
*/
Node_t** putString(char* key, const char* str, Node_t* hashTable[]){
  char* newVal = strdup(str);
  return put(key, newVal, hashTable);
}

/*
    The resize table algorithm is simple.
    1. First it determines if the density is high
       enough to warrant a resize.
    2. If the density is high enought it creates a brand new
       table.  The size of this new table is computed
       by taking the number of existing non-NULL nodes
       and multiplying that by the NEW_SIZE factor.
    3. The getAll function is called to retrieve all the
       nodes from the existing table.
    4. The nodes retrieved are then placed one by one
       into the new table so that the new values such as
       count, size, collision count are recalculated.
    5. The garbage is then cleaned out.
    **NOTE - The data from the old table is not cleaned
       because it is simply reused for the new table.
    returns a pointer to the new table.

    NOTE: another solution could have been to add one
    more level of indirection and use re-alloc but that
    was producing some really buggy run-time errors.

*/
Node_t** resizeTable(Node_t** hashTable){

    int nodeCount = countTable(hashTable);
    int oldTableSize = getTableSize(hashTable);
    int density = nodeCount / oldTableSize;

    DEBUGLOG("\nDensity: %d nodes per bucket", density);
    if(density < COLLISION_THRESHOLD){
      DEBUGLOG("\nNot resizing...");
      return hashTable;
    }
    DEBUGLOG("\nResizing....");


    Node_t** newTable = createTableX(nodeCount * NEW_SIZE_FACTOR);

    Node_t** allNodesTable = getAll(hashTable);
    
    DEBUGLOG("\n***CREATED ALL NODES***");
    /* disconnect all lists*/
    int i = 0;
    while(allNodesTable[i]){
        DEBUGLOG("\n****Putting node %d****", i);
        /*
          There is no need to capture the table since it will not resize
          from this put call.
        */
        put(allNodesTable[i]->key, allNodesTable[i]->data, newTable);
        i++;
        DEBUGLOG("\nin resizing after put i: %d %p", i, allNodesTable[i]);
    }
    
    for( i=0; i<oldTableSize; i++){
        Node_t* list = hashTable[i];

        Node_t* temp = list;
        Node_t* previous;

        while(temp != NULL){
            DEBUGLOG("!!!!IN RESIZE DELETEING OLD NODES!!!");
            previous = temp->next;

            //Free up meta data... that data is not reused
            if(i==0){
              free(temp->data); 
            }
            free(temp);
            
            temp = previous;
            
        }
    }

    free(hashTable);
    free(allNodesTable);

    return newTable;
}

/*
*  updateCollision count updates the highest collision count
*  in bucket 0 of the table.  Bucket zero is reserved for metadata.
*  only if the count is higher than the current value does it replaced
*  it.
*/
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

/*
*   This function is implemented similarly to updateCollisionCount.
*   It stores the non-NULL node count in bucket 0 (the bucket reserved
*   for meta data)
*/
void updateNodeCount(Node_t* hashTable[]){
    Node_t* node = findNode(NODE_COUNT_STR, hashTable[0]);

    if(node != NULL){
        int *count = node->data;
        *count = *count + 1;
        DEBUGLOG("\nNode count updated: %d", *count);
        //*((int*)node->data) = *count;
    }
}


