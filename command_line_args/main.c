#include "stdio.h"

int main(int argc, char* argv[]) {

  if(argc == 1){
      printf("\nOne argument %s", argv[0]);
  }
  else if(argc > 1){
      for(int i=0;i<argc;i++){
          printf("\nargc %d is %s", i, argv[i]);
      }
  }

  int ch = getc(stdin);
  
  return 0;
}