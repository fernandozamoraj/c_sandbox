#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

void countWordsInFile(int argc, char *argv[]);
void testResizing();
void testWithUserInput();
void sortAndDisplay(int lineCountParameter, Node_t* hashtable[]);

/*
   function for qsort to compare nodes descending
*/
int comp_values_descending(const void *a, const void *b);

int main(int argc, char *argv[])
{
    countWordsInFile(argc, argv);
    //testWithUserInput();

	return 0;
}

int comp_values_descending(const void *a, const void *b){

    Node_t *nodeA = *(Node_t**)a;
    Node_t *nodeB = *(Node_t**)b;

    int* aData = nodeA->data;
    int* bData = nodeB->data;
    return *bData - *aData;
}

void sortAndDisplay(int lineCountParameter, Node_t* hashtable[]){

	Node_t** all = getAll(hashtable);

	int nodeCount = 0;

    while(all[nodeCount] != NULL){
        nodeCount++;
    }

	int len = nodeCount;

	qsort(all, nodeCount, sizeof(Node_t*), comp_values_descending);

	if(lineCountParameter > 0){
        len = lineCountParameter;
	}

	/*safety in case user passed value greater than node count*/
	if(len > (nodeCount)){
        len = nodeCount;
	}

	for(int i=0; i < len;i++){
        int *val = all[i]->data;
        printf("\n%d. %d %s", i+1, *val, all[i]->key);
	}

	free(all);
}

void countWordsInFile(int argc, char *argv[]){
	char **fileOrPathNames = argv;

	char *words = NULL;

	int lineCountParameter = -1;

	Node_t** hashtable = createTableX(5);

	fileOrPathNames++;

	if(argc > 1){

        /*if the second argument starts with a dash*/
        if(argv[1][0] == '-'){
           lineCountParameter = atoi(argv[1]) * -1; /*make the number positive*/
           fileOrPathNames++; /*skip this parameter -- not a file name*/
        }
	}

	while(*fileOrPathNames)
	{

		char *actualFileName = *fileOrPathNames;

		FILE *fd;

		fd = fopen(actualFileName, "r");

		if(fd == NULL)
		{
            printf("\nUnable to open the file: %s\n", actualFileName);
			fprintf(stderr, "Unable to open the file: %s\n", actualFileName);
			exit(-1);
		}

		while((words = getNextWord(fd)) != NULL)
		{
			hashtable = incrementCount(words, hashtable);

			free(words);
		}

		fclose(fd);

		fileOrPathNames++;
	}

	sortAndDisplay(lineCountParameter, hashtable);
    printf("\n\n");
	deleteTable(hashtable);
}

void testWithUserInput(){

    char key[MAX_WORD_SIZE];
    char value[MAX_WORD_SIZE];
    Node_t** hashtable = createTable();
    char* searchValue;

    while(1){

        printf("\nEnter a key (q to quit): ");
        scanf("%s", key);

        if(strcmp(key, "q") == 0){
            break;
        }
        printf("\nEnter a value: ");
        scanf("%s", value);

        hashtable = putString(key, value, hashtable);
    }

    while(1){

        printf("\nEnter a search key (q to quit): ");
        scanf("%s", key);

        if(strcmp(key, "q") == 0){
            break;
        }

        Node_t* keyValue = get(key, hashtable);
        if(keyValue != NULL){
           searchValue = keyValue->data;
           printf("\nValue found: %s", searchValue);
        }
        else{
            printf("\nValue not found for key %s", key);
        }
    }
}

void testResizing()
{
    Node_t** hashTable = createTableX(3);

    printf("\n\n**************************************");
    printf("\nTable size %d", getTableSize(hashTable));

    hashTable = incrementCount("aa", hashTable);
    hashTable = incrementCount("bb", hashTable);
    hashTable = incrementCount("cc", hashTable);
    hashTable = incrementCount("dd", hashTable);
    hashTable = incrementCount("ee", hashTable);
    hashTable = incrementCount("ff", hashTable);
    hashTable = incrementCount("gg", hashTable);

    printf("\n\n*********************************");
    printf("\nCheck after 7 inserts");
    printf("\nTable size %d", getTableSize(hashTable));
    printf("\nHighest Collission %d", getHighestCollision(hashTable));

    hashTable = incrementCount("hh", hashTable);
    hashTable = incrementCount("ii", hashTable);
    hashTable = incrementCount("jj", hashTable);
    hashTable = incrementCount("kk", hashTable);
    hashTable = incrementCount("ll", hashTable);
    hashTable = incrementCount("mm", hashTable);

    printf("\n\n*********************************");
    printf("\nCheck after 13 inserts");
    printf("\nTable size %d", getTableSize(hashTable));
    printf("\nHighest Collission %d", getHighestCollision(hashTable));


    hashTable = incrementCount("nn", hashTable);
    hashTable = incrementCount("oo", hashTable);
    hashTable = incrementCount("pp", hashTable);
    hashTable = incrementCount("qq", hashTable);
    hashTable = incrementCount("rr", hashTable);
    hashTable = incrementCount("ss", hashTable);
    hashTable = incrementCount("tt", hashTable);
    hashTable = incrementCount("vv", hashTable);
    hashTable = incrementCount("xx", hashTable);
    hashTable = incrementCount("yy", hashTable);
    hashTable = incrementCount("zz", hashTable);

    printf("\n\n*********************************");
    printf("\nCheck after full alphabet");
    printf("\nTable size %d", getTableSize(hashTable));
    printf("\nHighest Collission %d", getHighestCollision(hashTable));


    hashTable = incrementCount("aa", hashTable);
    hashTable = incrementCount("bb", hashTable);
    hashTable = incrementCount("cc", hashTable);
    hashTable = incrementCount("dd", hashTable);
    hashTable = incrementCount("ee", hashTable);
    hashTable = incrementCount("ff", hashTable);
    hashTable = incrementCount("gg", hashTable);
    hashTable = incrementCount("hh", hashTable);
    hashTable = incrementCount("ii", hashTable);
    hashTable = incrementCount("jj", hashTable);
    hashTable = incrementCount("kk", hashTable);
    hashTable = incrementCount("ll", hashTable);
    hashTable = incrementCount("mm", hashTable);
    hashTable = incrementCount("nn", hashTable);
    hashTable = incrementCount("oo", hashTable);
    hashTable = incrementCount("pp", hashTable);
    hashTable = incrementCount("qq", hashTable);
    hashTable = incrementCount("rr", hashTable);
    hashTable = incrementCount("ss", hashTable);
    hashTable = incrementCount("tt", hashTable);
    hashTable = incrementCount("uu", hashTable);
    hashTable = incrementCount("vv", hashTable);
    hashTable = incrementCount("xx", hashTable);
    hashTable = incrementCount("yy", hashTable);
    hashTable = incrementCount("zz", hashTable);

    printf("\n\n*********************************");
    printf("\nCheck after updating full alphabet");
    printf("\nTable size %d", getTableSize(hashTable));
    printf("\nHighest Collission %d", getHighestCollision(hashTable));
    printf("\nNode count should be 26 and is %d", getNodeCount(hashTable));

    hashTable = incrementCount("1", hashTable);
    hashTable = incrementCount("2", hashTable);
    hashTable = incrementCount("3", hashTable);
    hashTable = incrementCount("4", hashTable);
    hashTable = incrementCount("5", hashTable);
    hashTable = incrementCount("6", hashTable);
    hashTable = incrementCount("7", hashTable);
    hashTable = incrementCount("8", hashTable);
    hashTable = incrementCount("9", hashTable);
    hashTable = incrementCount("10", hashTable);
    hashTable = incrementCount("11", hashTable);
    hashTable = incrementCount("12", hashTable);
    hashTable = incrementCount("13", hashTable);
    hashTable = incrementCount("14", hashTable);
    hashTable = incrementCount("15", hashTable);
    hashTable = incrementCount("16", hashTable);
    hashTable = incrementCount("17", hashTable);
    hashTable = incrementCount("18", hashTable);
    hashTable = incrementCount("19", hashTable);
    hashTable = incrementCount("20", hashTable);
    hashTable = incrementCount("21", hashTable);
    hashTable = incrementCount("22", hashTable);
    hashTable = incrementCount("23", hashTable);
    hashTable = incrementCount("24", hashTable);
    hashTable = incrementCount("25", hashTable);
    hashTable = incrementCount("26", hashTable);

    printf("\n*********************************");
    printf("\nAfter adding 26 new nodes");
    printf("\nTable size %d", getTableSize(hashTable));
    printf("\nHighest Collission %d", getHighestCollision(hashTable));
    printf("\nNode count should be 52 and is %d", getNodeCount(hashTable));
    printf("\n\n");


}
