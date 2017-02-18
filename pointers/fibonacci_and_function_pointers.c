#include "stdio.h"

/*
  I was playing around with the idea of implementing a for each using C.
  I'm not sure that it gets you much. However, I ran into solving fibonacci
  without recursion.

*/
void for_each(int* list, int length, void (*action)(int*)){
  
  int i = 0;
  
  while(i < length){
    action(list+i);
    i++;
  }
}

void display(int* x){
  printf("\n%d", *x);
}

/*
  set x equal to the sum of the previous 2 elements in the array (x-1 and x-2)
*/
void fib(int* x){
  
  *x = *(x-1) + *(x-2);
}

int main(void) {
  
  //initialize first two elements
  int my_array[100] = {0,1};


  //start the for each at element 2 since
  //elements 0 and 1 are already set
  for_each((my_array+2), 45, &fib);
  for_each(my_array,  45, &display);
  
  
  return 0;
}