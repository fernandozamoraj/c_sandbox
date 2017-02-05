#include <stdio.h>
#include "mystrings.h"


int main(void) {
  
  char name[30] = "Joe Smith 31";
  char holder[100] = {0};
  
  stringToUpper(holder, name);
  printf("\n %s", holder);
  stringToLower(holder, name);
  printf("\n %s", holder);
  
  printf("\n APPLE vs. apple %d", compareIgnoreCase("APPLE", "apple"));
  printf("\n APPLE vs. apple %d", strcmp("APPLE", "apple"));

  
  return 0;
}