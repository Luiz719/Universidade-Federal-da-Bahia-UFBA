#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
	int value;
	struct item *next;
}item;

typedef struct stack{
	struct item *top;
}stack;

item *NewItem(int a){
	item *element = (item*)malloc(sizeof(item));
	element-> value = a;
	element-> next = NULL;
	return element;
}

stack *NewStack(){
	stack *pile = (stack*)malloc(sizeof(stack));
	pile->top = NULL;
	return pile;
}

void Push(item *element, stack *pile){
	element-> next = pile->top;
	pile->top = element;
}

item *Pop(stack *pile){
    if(pile-> top != NULL){
        item *aux = pile-> top;
        pile-> top = aux-> next;
        return aux;
	}
	return NULL;
}

void DisplayStack(stack *pile){
    item *aux = pile-> top;
    while(aux != NULL){
        printf("%d\n", aux-> value);
        aux = aux-> next;
    }
}

void FreeStack(stack *pile){
    while(pile-> top != NULL){
        free(Pop(pile));
    }
    free(pile);
}

void Push_Stack(stack *second_pile, stack *first_pile){
    stack *aux_pile = NewStack();
    while(second_pile-> top != NULL){
        Push(Pop(second_pile), aux_pile);
    }
    FreeStack(second_pile);
    while(aux_pile-> top != NULL){
        Push(Pop(aux_pile), first_pile);
    }
    FreeStack(aux_pile);
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
            if(j == 0)
                Push(NewItem(list_items[i]), first_pile);
            else
                Push(NewItem(list_items[i]), second_pile);
		}
		free(list_items);
		free(size);
	}
	Push_Stack(second_pile, first_pile);
    DisplayStack(first_pile);
    FreeStack(first_pile);
	return EXIT_SUCCESS;
}

