#include<stdio.h>

/*
   Displays the contents of an myarray
*/
void displayArrayInt(int myarray[], int length){
    for(int i = 0; i < length; i++){
        printf("\nmyarray[%d]: %d", i, myarray[i]);
    }
}