#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
	int value;
	struct item *next;
}item;

typedef struct queue{
	struct item *first;
	struct item *last;
	int size;
}queue;

item *NewItem(int a){
	item *element = (item*)malloc(sizeof(item));
	element-> value = a;
	element-> next = NULL;
	return element;
}

queue *NewQueue(){
	queue *row = (queue*)malloc(sizeof(queue));
	row-> first = NULL;
	row-> last = NULL;
	row-> size = 0;
	return row;
}

int queueIsEmpty(queue *row){
    if(row-> size == 0)
        return 1;
    return 0;
}

void Append(item *element, queue *row){
    if(queueIsEmpty(row)){
        row-> first = element;
        row-> last = element;
    }else{
        row-> last-> next = element;
        row-> last = element;
    }
	row-> size += 1;
}

item *Pop(queue *row){
    if(row-> first != NULL){
        item *aux = row-> first;
        row-> first = aux-> next;
        row-> size -= 1;
        aux-> next = NULL;
        return aux;
	}
	return NULL;
}

void Display(queue *row){
    item *aux = row-> first;
    while(aux != NULL){
        printf("%d ", aux-> value);
        aux = aux-> next;
    }
    printf("\n");
}

void FreeQueue(queue *row){
    while(row-> first != NULL){
        free(Pop(row));
    }
    free(row);
}

//Início de pilhas
typedef struct stack{
	struct item *top;
	int size;
}stack;

stack *NewStack(){
	stack *pile = (stack*)malloc(sizeof(stack));
	pile-> top = NULL;
	pile-> size = 0;
	return pile;
}

void Push(item *element, stack *pile){
	element-> next = pile->top;
	pile-> top = element;
	pile-> size += 1;
}

item *PopStack(stack *pile){
    if(pile-> top != NULL){
        item *aux = pile-> top;
        pile-> top = aux-> next;
        pile-> size -= 1;
        aux-> next = NULL;
        return aux;
	}
	return NULL;
}

void DisplayStack(stack *pile){
    item *aux = pile-> top;
    int print[pile-> size];
    int counter = 0;
    while(aux != NULL){
        print[counter] = aux-> value;
        aux = aux-> next;
        counter++;
    }
    for(int i = pile-> size - 1; i >= 0; i--)
        printf("%d ", print[i]);
    printf("\n");
}

void FreeStack(stack *pile){
    while(pile-> top != NULL){
        free(PopStack(pile));
    }
    free(pile);
}
//Fim de pilhas

void StackInQueue(stack *pile, queue *row){
    stack *aux_pile = NewStack();
    while(pile-> top != NULL){
        Push(PopStack(pile), aux_pile);
    }
    while(aux_pile-> top != NULL){
        Append(PopStack(aux_pile), row);
    }
}

queue *MixQueues(queue *first_row, queue *second_row){
    queue *final_row = NewQueue();
    if(first_row-> size <= second_row-> size){
        while(!queueIsEmpty(first_row)){
            Append(Pop(first_row), final_row);
            Append(Pop(second_row), final_row);
        }
        while(!queueIsEmpty(second_row)){
            Append(Pop(second_row), final_row);
        }
    }else{
        while(!queueIsEmpty(second_row)){
            Append(Pop(first_row), final_row);
            Append(Pop(second_row), final_row);
        }
        while(!queueIsEmpty(first_row)){
            Append(Pop(first_row), final_row);
        }
    }
    return final_row;
}

int *getElements(char *string, int *size){
	int *list_items = (int*)malloc(0 * sizeof(int));
	int i = 0;
	char* token = strtok(string, " ");
	while(token){
		i += 1;
		list_items = (int*)realloc(list_items, sizeof(int)* i);
		list_items[i-1] = atoi(token);
		token = strtok(NULL, " ");
    }
	*size = i;
	free(token);
	return list_items;
}

int main(int argc, char **argv){
    queue *first_row = NewQueue();
    queue *second_row = NewQueue();
    queue *final_row;
    stack *first_pile = NewStack();
    stack *second_pile = NewStack();
	char *string = NULL;
	size_t len = 0;
	getline(&string, &len, stdin);
	int total_lines = atoi(string);
	free(string);
	for(int j = 0; j < total_lines; j++){
		int *size = (int*)malloc(sizeof(int));
		string = NULL;
		len = 0;
		getline(&string, &len, stdin);
		int* list_items = getElements(string, size);
		free(string);
		for(int i = 0; i < *size; i++){
		    if(!j)
                Push(NewItem(list_items[i]), first_pile);
            else
                Push(NewItem(list_items[i]), second_pile);
		}
        free(list_items);
		free(size);
	}
	DisplayStack(first_pile);
	DisplayStack(second_pile);
	StackInQueue(first_pile, first_row);
	StackInQueue(second_pile, second_row);
	Display(first_row);
	Display(second_row);
	final_row = MixQueues(first_row, second_row);
	Display(final_row);
	FreeQueue(final_row);
	FreeQueue(first_row);
	FreeQueue(second_row);
	FreeStack(first_pile);
	FreeStack(second_pile);
	return EXIT_SUCCESS;
}

