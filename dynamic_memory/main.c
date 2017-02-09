#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//tag is required for nested type
typedef struct Node{
    int data;
    struct Node* next;
    struct Node* previous;
} Node_t;

Node_t* createNode(){
    Node_t* pNode = malloc(sizeof(Node_t));
    pNode->data = 0;
    pNode->next = NULL;
    pNode->previous = NULL;

    return pNode;
}

Node_t* add(Node_t** head, Node_t** tail, int data){
    if(*head == NULL){
        *head = createNode();
        (*head)->data = data;
        (*head)->next = NULL;
        (*head)->previous = NULL;
        (*tail) = (*head);
        return *head;
    }
    else{
        Node_t *pTemp = *head;
        Node_t *pPrevious = pTemp;
        //0[1, next: 1, previous: NULL ]->1[3, next: 2, previous:0]->2[5, next:NULL, previous: 2]
        while(pTemp != NULL){
        
            if(pTemp->next == NULL){
                pTemp->next = createNode();
                pTemp->next->data = data;
                pTemp->next->next = NULL;
                pTemp->next->previous = pTemp;
                *tail = pTemp->next;
                break;
            }
            pTemp = pTemp->next;
        }
    }

    return *head;
}

void displayList(Node_t* list){
    Node_t* temp = list;

    while(temp != NULL){
        printf("\ntemp->data %d", temp->data);
        temp = temp->next;
    }
}

Node_t* findItemInList(Node_t* head, int data){
    Node_t* temp = head;

    while(temp != NULL){
        if(temp->data == data){
            return temp;
        }
        temp = temp->next;
    }
}

void destroyList(Node_t* tail){
    Node_t* temp;

    while(tail != NULL){
        temp = tail;
        tail = tail->previous;
        printf("\ndestroying %d", temp->data);
        free(temp);        
    }
}

int main(void){
    time_t t;
    Node_t* head = NULL;
    Node_t* tail = NULL;
    srand((unsigned)time(&t));

    for(int i = 0; i < 30; i++){
        add(&head, &tail, rand()%100);    
    }

    displayList(head);

    int value = 0;
    
    while(1){
        printf("\nEnter value (0 to quit): ");
        scanf("%d", &value);
    
        if(value == 0)
            break;
        Node_t* temp = findItemInList(head, value);
        
        if(temp != NULL)
            printf("\n%d", temp->data);
        else
            printf("\nValue not found.");
    }



    destroyList(tail);
}




