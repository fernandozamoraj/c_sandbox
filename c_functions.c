#include "stdio.h"
#include <string.h>

/*
for git demo
  2. Comparing string arrays with strings
*/
void compareCharArrayToString(){
  char s1[] = {'a', 'b', 'c', '\0'};
  char s2[] = "abc";
  char chArray[] = {'a', 'b', 'c'}; //no terminating character
  
  printf("\n\n********compareCharArrayToString****");
  if(strcmp(s1, s2) == 0){
    printf("\ns1 == s2");
  }
  
  if(strcmp(s1, chArray) == 0){
    printf("\ns1 == chArray");
  }
  else{
    printf("\ns1 != chArray");
  }

  printf("\n");
  printf(chArray);
}

/*
   1. Using string comparisons
*/
void usingStringCompare(){

  printf("\n\n********usingStringCompare****");
  
  if(strcmp("ab", "bc") < 0){
    printf("\na < b");
  }
   
  printf("\n\n strcmp(\"ab\", \"AB\") is %d", strcmp("ab", "AB"));
  printf("\n strcmp(\"ab\", > \"AB\") > 0");
  
  printf("\n\n strcmp(\"aa\", \"zz\") is %d", strcmp("aa", "zz"));
  printf("\n strcmp(\"aa\", < \"zz\") < 0");
  
  printf("\n\n strcmp(\"aa\", \"aa\") is %d", strcmp("aa", "aa"));
  printf("\n strcmp(\"aa\", == \"aa\") == 0");

  printf("\n\n strcmp(\"zz\", \"aa\") is %d", strcmp("zz", "aa"));
  printf("\n strcmp(\"zz\", > \"aa\") > 0");
  
}

/*
   2.1 copying over strings
*/
void usingStringCopy(){
  
  printf("\n\n********usingStringCopy****");
  char name1[30] = {0};
  char name2[30] = "Joe";
  
  strcpy(name1, name2);
  
  printf("\nname1: %s", name1);
  
  
}

/*
  3. Join strings together (concatenate)
*/
void usingStringConcatenate(){
  printf("\n\n********usingStringConcatenate****");
  char s1[10] = "bob";
  char s2[] = "cat";
  
  printf("\ns1 %s", s1);
  strcat(s1, s2);
  printf("\nafter strcat s1 %s", s1);
  
}

/*
  4. Creating strings using sprintf
*/
void formatWithSPrintF(){

  printf("\n\n********formatWithSPrintF****");
  int age = 30;
  char name[] = "Joe Smith";
  char phone[] = "555-444-1111";
  char newString[100];
  sprintf(newString, "\n\nName: %s \nage: %d \nphone: %s", name, age, phone);
  
  printf(newString);
  
  
}



/*
  5. passing string parameters
*/
void passingStringsToFunctions(
  char* firstName, 
  const char* lastName,  //const char* to prevent changes
  char phone[]){

  printf("\n\n********passingStringsToFunctions****");
  
  strcpy(firstName, "Joe");
  
  printf("\nFirst Name : %s", firstName);
  printf("\nLast Name  : %s", lastName);
  printf("\nPhone:     : %s", phone);
  
  
}

int main(void) {

  usingStringCompare();
  compareCharArrayToString();
  usingStringCopy();
  usingStringConcatenate();
  formatWithSPrintF();
  
  char firstName[30] = "John";
  char lastName[30] = "smith";
  passingStringsToFunctions(firstName, lastName, "555-444-1111");
  
  return 0;
}