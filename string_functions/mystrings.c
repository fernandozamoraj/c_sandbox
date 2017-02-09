#include "mystrings.h"

char* stringToUpper(char* myString, const char* source){
   strcpy(myString, source);
   
   while(*myString != '\0'){
     if(islower(*myString)){
       *myString = toupper(*myString); 
     }
     myString++;
   }
   
   return myString;
}

char* stringToLower(char* myString, const char* source){
  
   strcpy(myString, source);
   
   while(*myString != '\0'){
     if(isupper(*myString)){
       *myString = tolower(*myString); 
     }
     myString++;
   }
   
   return myString;
}

int compareIgnoreCase(const char* s1, const char* s2){
  char holder1[255];
  char holder2[255];
  
  strcpy(holder1, s1);
  strcpy(holder2, s2);
  stringToLower(holder1, s1);
  stringToLower(holder2, s1);
  
  return strcmp(holder1, holder2);
}

