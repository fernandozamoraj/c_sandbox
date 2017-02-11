#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LEN 200
#define NAME_LEN 30
#define TRUE 1
#define FALSE 0

typedef struct{
    char firstName[NAME_LEN+1];
    char lastName[NAME_LEN+1];
    int age;
    float gpa;
} Student;

char* trim(char* src, int maxLength){
    
    *(src+(maxLength-1)) = '\0';
}
Student parseStudentFixed(char* line){
    Student student;
    char temp[20] = {0};
    
    //strncpy copies from the given pointer 
    //the indicated number of characters
    //TODO: write a trim function to remove trailing
    //      spaces challenge for you!!!!

    strncpy(student.firstName, line, 10);
    student.firstName[10] = '\0';

    strncpy(student.lastName, (line + 10), 10);
    student.lastName[10] = '\0';

    student.age = atoi(strncpy(temp, (line + 20), 3));
    student.gpa = atof(strncpy(temp, (line + 23), 3));

    return student;
}

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

/*
    We are solely making the determination on 
    whether the file contains "fixed" as part of
    it's name (e.g. student_fixed.dat)
*/
int strContains(const char* src, const char* substring ){
    char* needle = strstr(src, substring);

    if(needle != NULL){
        return TRUE;
    }

    return FALSE;
}

void setFileName(char* fileName, int argc, char* argv[]){
    if(argc > 1){
        strcpy(fileName, argv[1]);
    }
    else{
        strcpy(fileName, "C:\\dev\\temp\\students.csv");
    }
}

void logit(char* line){
    printf("\n%s", line);
}

int main(int argc, char* argv[]){

    FILE *fp = NULL;
    char fileName[255] = {0};
    char line[LINE_LEN+1];
    Student student;
    int fixedLength = FALSE;

    logit("setting file name");
    setFileName(fileName, argc, argv);
    logit("entering strContains");
    fixedLength = strContains(fileName, "fixed"); 

    printf("\nFile is fixed: %d", fixedLength);
 
    printf("\nReading file %s", fileName);
    
    fp =  fopen(fileName, "r");
    
    if(fp != NULL){

        printf("\nContents of file:\n");
        while(fgets(line, LINE_LEN, fp) != NULL){
            
            if(fixedLength){                
                student = parseStudentFixed(line);
            }
            else{
                student = parseStudent(line);
            } 
            printStudent(student);
        }
        
        fclose(fp);
    }

    return 0;
}