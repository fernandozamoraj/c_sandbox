#include <stdio.h>
#include <stdlib.h>

int main(void){

    FILE *fp = fopen("main.c", "r");
    char line[100];

    if(fp != NULL){

        while(fgets(line, 80, fp) != NULL){
            printf("%s", line);
        }
    }

    return 0;
}