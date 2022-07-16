#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
	int value;
	struct item *next;
}item;

typedef struct stack{
	struct item *top;
	int size;
}stack;

item *NewItem(int a){
	item *element = (item*)malloc(sizeof(item));
	element-> value = a;
	element-> next = NULL;
	return element;
}

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

item *Pop(stack *pile){
    if(pile-> top != NULL){
        item *aux = pile-> top;
        pile-> top = aux-> next;
        pile-> size -= 1;
        return aux;
	}
	return NULL;
}

void DisplayStack(stack *pile){
    item *aux = pile-> top;
    while(aux != NULL){
        printf("%d ", aux-> value);
        aux = aux-> next;
    }
    printf("\n");
}

void FreeStack(stack *pile){
    while(pile-> top != NULL){
        free(Pop(pile));
    }
    free(pile);
}

void Move_Aux(stack *pile, stack *final_pile){
    if(pile-> size == 0){
        Push(Pop(final_pile), pile);
    }else if(final_pile-> size == 0){
        Push(Pop(pile), final_pile);
    }else if(pile-> top-> value > final_pile-> top-> value){
        Push(Pop(final_pile), pile);
    }
    else{
        Push(Pop(pile), final_pile);
    }
}

stack *Move_Stack(stack *pile){
    stack *aux_pile = NewStack();
    stack *final_pile = NewStack();
    int steps = 0;
    int goal = pile-> size;
    while(final_pile-> size != goal){
        if(goal % 2 == 0){
            Move_Aux(pile, aux_pile);
            steps += 1;
            Move_Aux(pile, final_pile);
            steps += 1;
            if(final_pile-> size == goal)
                break;
            Move_Aux(aux_pile, final_pile);
            steps += 1;
        }else{
            Move_Aux(pile, final_pile);
            steps += 1;
            if(final_pile-> size == goal)
                break;
            Move_Aux(pile, aux_pile);
            steps += 1;
            Move_Aux(aux_pile, final_pile);
            steps += 1;
        }
    }
    printf("%d", steps);
    return final_pile;
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
    stack *pile = NewStack();
    stack *final_pile;
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
            Push(NewItem(list_items[i]), pile);
		}
		free(list_items);
		free(size);
	}
	final_pile = Move_Stack(pile);
	FreeStack(final_pile);
	FreeStack(pile);
	return EXIT_SUCCESS;
}

