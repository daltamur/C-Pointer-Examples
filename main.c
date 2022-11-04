#include <stdio.h>
#include <string.h>
#include <malloc.h>


typedef struct
{
    int *rmNumber;
    int *rmCleanliness;
    int *north;
    int northNoPointer;
} Room;


void changePointerValue(int *myPointer){
    *myPointer = (*myPointer) + 5;


}

typedef struct
{
    struct node *nextNode;
    int value;
}node;


void fillUpMatrix(int **matrix){
    for(int i = 0 ; i< 3; i++){
        //make a row
        //this is the same as matrix[i] = malloc(sizeof (int) * 3), but pointer arithmetic is cooler and as soon
        //as someone sees two asterisks on the same line they give you a job at Apple;
        *(matrix+i) = malloc(sizeof (int) * 3);
        for(int j = 0; j<3; j++ ){
            //fill up the row
            //this is the same as matrix[i][j] = j
            //*(matrix+i) looks at the row value (think of it like getting a value from a single array)
            //*(*(matrix+i)+j) looks at a cell value where *(matrix+i) is the row value to reference
            //and the +j part is what row we are looking at.
            *(*(matrix+i)+j) = j;
        }
    }
}


void freeMatrixMemory(int **matrix){
    for(int i = 0 ; i< 3; i++){
        //just deallocate memory for each row pointer
        //the parentheses in *(matrix+i) are important because it signifies exactly what row we are deallocating at (matrix+i)
        free(*(matrix+i));
    }
    //deallocate memory for entire thing
    free(matrix);
}

void freeIntMemory(int *pointer){
    free(pointer);
}

void freeIntArrayMemory(int *arrayPointer){
    free(arrayPointer);
}

void fillUpSomeRoomStructVals(Room *room){
    room->north = malloc(sizeof(int));
    *(room->north) = 52;

    room->rmNumber = malloc(sizeof(int));
    *(room->rmNumber) = 23423;

    room->rmCleanliness = malloc(sizeof(int));
    *(room->rmCleanliness) = 3;

    room->northNoPointer = 54;
}

void freeStructMemory(Room *room){
    free(room->north);
    free(room->rmNumber);
    free(room->rmCleanliness);
    free(room);
}


void addNodeToList(int addedVal, node* curNode){
    if(curNode->nextNode == NULL){
        node *nextPointer = malloc(sizeof(node));
        nextPointer->nextNode = NULL;
        nextPointer->value = addedVal;
        curNode->nextNode = (struct node *) nextPointer;
    }else{
        addNodeToList(addedVal, (node *) curNode->nextNode);
    }
}

void freeListNode(node* curNode){
    if(curNode -> nextNode == NULL){
        free(curNode);
    }else{
        freeListNode((node *) curNode->nextNode);
        free(curNode);
    }
}

node* removeListNode(int removeVal, node *curNode) {
    //this is for a singly linked list, it would actually be easier if we were using a doubly linked list!
    //try and make a doubly linked list and apply the methods I provided!
    if(curNode -> value == removeVal){
        return (node *) curNode->nextNode;
    }else{
        node* returnedVal = removeListNode(removeVal, (node *) curNode->nextNode);
        if(returnedVal != NULL){
            curNode->nextNode = (struct node *) returnedVal;
            return NULL;
        }
    }
}


void traverseList(node* curNode){
    printf("%d\n", curNode->value);
    if(curNode->nextNode != NULL){
        traverseList((node *) curNode->nextNode);
    }
}

int main() {
    //basic pointer stuff
    printf("Basic pointer stuff\n");
    int *val = malloc(sizeof(int));
    *val = 0;
    changePointerValue(val);
    printf("%d\n", *val);
    freeIntMemory(val);

    //pointer arithmetic
    int *Vals = malloc(sizeof(int)*3);
    for(int i = 0; i<3; i++){
        *(Vals+i) = i;
    }

    printf("\n");
    printf("pointer array stuff\n");

    for(int i = 0; i<3; i++){
        printf("%d\n", *(Vals+i));
    }

    freeIntArrayMemory(Vals);
    printf("\n");


    //struct pointers
    printf("Using a room struct\n");
    Room *roomStruct = malloc(sizeof(Room));
    //The arrow acts as a dereferencer
    fillUpSomeRoomStructVals(roomStruct);
    printf("%d\n", *(roomStruct->rmCleanliness));
    printf("%d\n", *(roomStruct->north));
    printf("%d\n", *(roomStruct->rmNumber));
    printf("%d\n", roomStruct->northNoPointer);
    freeStructMemory(roomStruct);



    printf("\n");
    printf("2D Matrix (We use double pointers here!)\n");
    //2D array
    int **matrix = malloc(sizeof(int*) * 3);
    fillUpMatrix(matrix);


    for(int i = 0 ; i< 3; i++){
        for(int j = 0; j<3; j++ ){
            printf("%d ",*((*(matrix+i))+j));
        }
        printf("\n");
    }
    freeMatrixMemory(matrix);


    printf("\n");
    printf("Linked List \n");
    node *head = malloc(sizeof (node));
    head->nextNode = NULL;
    head->value = 18;
    addNodeToList(5, head);
    addNodeToList(8, head);
    addNodeToList(12, head);

    printf("List before removal of 8: \n");
    traverseList(head);
    removeListNode(8, head);
    printf("\n");
    printf("List after removal of 8: \n");
    traverseList(head);
    freeListNode(head);

    return 0;
}
