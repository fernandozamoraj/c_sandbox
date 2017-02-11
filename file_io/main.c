#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LEN 100
#define NAME_LEN 30

typedef struct{
    char firstName[NAME_LEN+1];
    char lastName[NAME_LEN+1];
    int age;
    float gpa;
} Student;

Student parseStudent(char* line){
    const char delimiter[2] = ",";
    Student student;
    char* token = strtok(line, delimiter);
    int i = 0;

    while(token != NULL){
        if(i==0){
            strcpy(student.firstName, token);
        }
        if(i==1){
            strcpy(student.lastName, token);
        }
        if(i==2){
            student.age = atoi(token);
        }
        if(i == 3){
            student.gpa = atof(token);
        }        
        
        token = strtok(NULL, delimiter);
        i++;
    }


    return student;
}

void printStudent(Student student){
    printf("\n\n**********STUDENT***********");
    printf("\nFirst:  %s", student.firstName);
    printf("\nLast:   %s", student.lastName);
    printf("\nAge:    %d", student.age);
    printf("\nGPA:    %0.1f", student.gpa);
}

int main(int argc, char* argv[]){

    FILE *fp = NULL;
    
    if(argc > 1){
        printf("\nReading file %s", argv[1]);
        fp =  fopen(argv[1], "r");
    }
    else{
        printf("\nReading file C:\\dev\\temp\\students.csv");
        fp = fopen("C:\\dev\\temp\\students.csv", "r");
    }

    char line[LINE_LEN+1];
    Student student;

    if(fp != NULL){

        printf("\nContents of file:\n");
        while(fgets(line, LINE_LEN, fp) != NULL){
            student = parseStudent(line);
            printStudent(student);
        }
        
        fclose(fp);
    }

    return 0;
}