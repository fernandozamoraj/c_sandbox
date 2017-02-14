
// Serene Ghazi
// Assignment 2
// January 30th 2017
// CS 261

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_SIZE 256

// define a structure called wordCount which holds
// the word and its frequency(count of word in the files), a pointer
// to itself such that it acts a next pointer in the linked list
struct wordCount
{
	char *word;
	int count;
	struct wordCount *next;
};

// declare the requried function prototypes
// to create a new link
struct wordCount *newLink();

// to add words if they are new or to increment the counter of the respective 
// word in the list
struct wordCount *addWords(struct wordCount *listWords, char *word);

// to search for the word in the list
int searchWord(struct wordCount *listWords, char *word);

// to print the list of words and their respective count value
void printWords(struct wordCount *listWords);

// to travel through each link and delete the links of listWords
void deleteListWords(struct wordCount *listWords);

// to get the next word in the list
char *getNextWord(FILE *fd);

// define the main which accepts two parameters
int main(int argc, char *argv[])
{

     //TODO: should check argc for a value greater than 1 otherwise exit
	// array of strings which holds the values
	// passed through the arguments
	char **fileOrPathNames = argv;

	// to hold the word return by the getNextWord()
	// function
	char *words = NULL;

	struct wordCount *listWords = newLink();
	
	listWords->next = NULL;


	// increment the fileOrPathNames array before hand
	// so as to access the actual file names present in the
	// arguments
	fileOrPathNames++;

	// loop until the array is empty
	while(*fileOrPathNames)
	{
		// define a variable to hold the single file name
		// passed in the array fileOrPathNames at respective index
		char *actualFileName = *fileOrPathNames;

		// declare the file pointer
		FILE *fd;

		// open the file name and point the pointer fd to the file
		fd = fopen(actualFileName, "r");

		// condition to check whether the file pointer fd is null
		// or not
		if(fd == NULL)
		{
			// if it is NULL, then print an error message to the
			// stderr and exit the program
			fprintf(stderr, "Unable to open the file: %s\n", actualFileName);
			exit(-1);
		}

		// loop to continuously read the words from the file
		// by using the getNextWord() function.
		while((words = getNextWord(fd)) != NULL)
		{
			// call the function addWords() by passing the linkedlist listWords and
			// the word store the return pointer of the struct wordCount(linkedlist) into
			// listWords
			listWords = addWords(listWords, words);

			// free the word
			free(words);
		}

		// close the file once, the fd reaches the end of the file
		fclose(fd);

		// increment the array pointer fileOrPathNames
		fileOrPathNames++;
	}

	// call the function printWords() to the list in specified format by passing
	// the listWords
	printWords(listWords);

	// call the function deleteListWords() to traverse through the list and
	// delete each node
	deleteListWords(listWords);

	// return from the main
	return 0;
}

// getNextWord() function: This function accepts a file pointer which
// points to the open file and returns a string
char *getNextWord(FILE *fd)
{
	// define and declare the requried variables
	int index = 0;

	// to hold each character read from the file
	int charValue;

	// define a string which can hold a string of capacity of
	// MAX_WORD_SIZE
	char word[MAX_WORD_SIZE];

	// loop until the file pointer reaches EOF
	while((charValue = fgetc(fd)) != EOF)
	{
		// condition to check whether the charValue is a space or not
          //TODO: what about these characters(),.'
          //'s should also be skipped as in petrel's
          //shouldn't they be skipped? 
          //you should probably write a routine to scrube the words
          //such end of sentence and any apostrophes 
		if(isspace(charValue))
		{
			// if space then set the string terminator at index
			word[index] = '\0';

			// return the new word that is obtained by strdup
			// by creating a new memory in the heap
			return (char *)strdup(word);
		}

		// if not space, check the condition whether the index value reaches
		// the MAX_WORD_SIZE - 1 and charValue is an alpha_numeric value or not
		else if(((index + 1) != (MAX_WORD_SIZE - 1)) && (isalnum(charValue)))
		{
			// if the index does not reaches the MAX_WORD_SIZE - 1
			// and charValue is an alpha_numeric then convert the
			// charValue to lower case and set the charValue into
			// word array at index
			charValue = tolower(charValue);
			word[index] = charValue;
		}

		// if above condition fails, then set the word at index to string
		// terminator and return a new copy of the word created in the heap
		// by using the strdup
		else
		{
			word[index] = '\0';

			return (char *)strdup(word);
		}

		// increment the index value
		index++;
	}

	// if nothing is returned through the loop, then return a NULL value
	return NULL;
}

//newLink() that takes no arguments and returns a
//struct wordCount pointer that creates a new node
struct wordCount *newLink()
{
	struct wordCount *ptr = (struct wordCount *)malloc(sizeof(struct wordCount));

     //TODO: set ptr->next == NULL here instead... better data encapsulation
	return ptr;
}

// addWords() function to add the word to the linked list listWords. This accepts 
// a struct wordCount pointer(linkedList) and a string and returns a pointer of
// the struct wordCount(linked list)

struct wordCount *addWords(struct wordCount *listWords, char *word)
{
	// declare two pointer to the struct wordCount
	struct wordCount *temp, *newWord;

	// call the function searchWord() by passing a listWords pointer and the word
	// and store the return value into the found variable
	int found = searchWord(listWords, word);

	// if found is 0, it means word to be inserted is a new word to the list
	if(found == 0)
	{
		//create a new node
		newWord = newLink();

		//set the value to the node
		newWord->word = (char *)strdup(word);
		newWord->count = 1;
		newWord->next = NULL;

		// if the listWords is null, that means there are no words in the list
		// then add the newWord pointer to the listWords link
		if(listWords == NULL)
		{
			listWords = newWord;
		}

		// if listWords is not empty, then iterater through the link and
		// add the word to the end of the list
		else
		{
			// place the listWords pointer to the temp
			temp = listWords;

			//loop through whole list
			while(temp->next != NULL)
			{
				// increment the pointer temp
				temp = temp->next;
			}

			// insert the newWord pointer to the end of the list
			temp->next = newWord;
		}
	}

	// if the word is found in the list then increment the respective 
	// count of link pointer
	else
	{
		// initialize the temp with next pointer of the listWords
		temp = listWords->next;

		//loop through whole linked list
		while(temp != NULL)
		{
			// check the condition whether the word matches the word in
			// the temp list if found increment the temp count value
			if(strcmp(temp->word, word) == 0)
			{
				temp->count++;
			}

			// if not found, move to next link
			temp = temp->next;
		}
	}

	// return the listWords pointer
	return listWords;
}

// searchWord() function to sarch the word to the linked list listWords. 
// This accepts a struct wordCount pointer(linkedList) and a string and 
// returns a int value(which specified found or not. if 0 not found, 1 found)
int searchWord(struct wordCount *listWords, char *word)
{
	// place the next pointer value into the temp pointer
	struct wordCount *temp = listWords->next;

	//loop through whole linked list    
	while(temp != NULL)
	{
		// if the word in found in the list temp, then return 1
		if(strcmp(temp->word, word) == 0)
		{
			return 1;
		}

		// if not found, move to the next pointer
		temp = temp->next;
	}

	// if word is not found in the entier list, then return 0
	return 0;
}

// printWords() function to print word and its frequency of occurrence in
// linked list listWords. 
// This accepts a struct wordCount pointer(linkedList)
void printWords(struct wordCount *listWords)
{
	// place the next pointer value into the temp pointer
	struct wordCount *temp = listWords->next;

	//loop through whole linked list    
	while(temp != NULL)
	{
		// print the value to the standard output
		printf("%10d %s\n", temp->count, temp->word);

		// move to the next pointer
		temp = temp->next;
	}
}

// deleteListWords() function to delete each node(link) pointer
// of linked list listWords. 
// This accepts a struct wordCount pointer(linkedList) 
void deleteListWords(struct wordCount *listWords)
{
	//declare the required variable
	struct wordCount *prev, *current = NULL;

	//initialize the current pointer with listWords
	current = listWords;

	//loop till current becomes NULL
     //TODO: verify that it frees the actual word in the STRUCT
	while(current != NULL)
	{
		prev = current->next;
          //TODO: free(current->word);
		free(current);
		current = prev;
	}

	//set the final value of header next to NULL
     //TODO:
     //!!!!!!list words was the first item deleted
     //should not do this
     //you can test by using the printf statement printf(“\nlistwords address %#010”, listWords);
     //do one before the loop and one after the loop
     //it will have different values  
	listWords->next = NULL;
}
