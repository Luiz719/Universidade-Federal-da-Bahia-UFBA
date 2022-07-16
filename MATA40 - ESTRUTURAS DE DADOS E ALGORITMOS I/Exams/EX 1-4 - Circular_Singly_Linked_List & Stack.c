#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
	int value;
	struct item *next;
}item;

typedef struct list{
	struct item *head;
}list;

list *NewList(){
	list *unit = (list*)malloc(sizeof(list));
	unit-> head = NULL;
	return unit;
}

item *NewItem(int a){
	item *element = (item*)malloc(sizeof(item));
	element-> value = a;
	element-> next = NULL;
	return element;
}

void Append(list *unit, item *element){
	if(unit-> head == NULL){
		unit-> head = element;
		element-> next = unit-> head;
	}else{
		item *aux = unit-> head;
		while(aux-> next != unit-> head)
			aux = aux-> next;
		aux-> next = element;
		element-> next = unit-> head;
	}
}

void Display(list *unit){
	item *aux = unit-> head;
    while(aux-> next != unit-> head){
        printf("%d ", aux-> value);
        aux = aux-> next;
    }
    printf("%d\n", aux-> value);
}

void Insert(list *unit, item *element, int pos){
    item *last_aux = unit-> head;
    int counter = 0;
    while(last_aux-> next != unit-> head && counter != pos - 1){
        last_aux = last_aux-> next;
        counter++;
    }
    if(pos == 0){
        element-> next = unit-> head;
        unit-> head = element;
        last_aux-> next = element;
    }else if(last_aux-> next == unit-> head){
        last_aux-> next = element;
        element-> next = unit-> head;
    }else{
        element-> next = last_aux-> next;
        last_aux-> next = element;
    }
}

int PopList(list *unit, int pos){
    item *last_aux = unit-> head;
    int value, counter = 0;
    while(last_aux-> next != unit-> head && counter != pos - 1){
        last_aux = last_aux-> next;
        counter++;
    }
    if(pos == 0){
        item *aux = unit-> head;
        unit-> head = aux-> next;
        last_aux-> next = unit-> head;
        value = aux-> value;
        free(aux);
        return value;
    }else{
        item *aux = last_aux-> next;
        last_aux-> next = aux-> next;
        value = aux-> value;
        free(aux);
        return value;
    }
	return -1;
}

void FreeList(list *unit){
    item *last_aux = unit-> head;
    while(last_aux-> next != unit-> head){
        last_aux = last_aux-> next;
    }
    while(unit-> head != last_aux){
        item *aux = unit-> head;
        unit-> head = aux-> next;
        free(aux);
    }
    free(last_aux);
    free(unit);
}

//Início de pilhas
typedef struct stack{
	struct item *top;
}stack;

stack *NewStack(){
	stack *pile = (stack*)malloc(sizeof(stack));
	pile->top = NULL;
	return pile;
}

void Push(item *element, stack *pile){
	element-> next = pile->top;
	pile->top = element;
}

int Pop(stack *pile){
    int value;
    if(pile-> top != NULL){
        item *aux = pile-> top;
        pile-> top = aux-> next;
        value = aux-> value;
        free(aux);
        return value;
	}
	return -1;
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
        Pop(pile);
    }
    free(pile);
}

stack *Search_List(list *unit){
    item *aux = unit-> head;
    stack *sorted_pile = NewStack();
    int ok_togo = 1, removed = 0, last = 0;
    int counter = 0, seen = 0, rounds = 0;
    int bigger = unit-> head-> value;
    while(1){
        ok_togo = 1;
        if(aux-> value == bigger && seen == 1){
            seen = 2;
        }else if(aux-> value > bigger){
            bigger = aux-> value;
            if(!removed && aux-> next == unit-> head){
                seen = 2;
                last = 1;
            }else
                seen = 1;
        }
        if(aux-> next == unit-> head){
            removed = 0;
            if(seen != 2)
                seen = 1;
            rounds++;
        }
        if(aux-> value == bigger && seen == 2){
            if(aux-> next == unit-> head && aux-> next-> next == aux && !last)
                rounds--;
            aux = aux-> next;
            Push(NewItem(PopList(unit, counter)), sorted_pile);
            bigger = aux-> value;
            if(aux != unit-> head)
                removed = 1;
            if(aux-> next == aux){
                Push(NewItem(PopList(unit, 0)), sorted_pile);
                break;
            }
            ok_togo = 0;
            seen = 0;
            last =0;
        }
        if(ok_togo)
            aux = aux-> next;
        if(aux == unit-> head)
            counter = 0;
        else
            counter++;
    }
    printf("%d\n", rounds);
    return sorted_pile;
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
    list *unit = NewList();
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
            Append(unit, NewItem(list_items[i]));
		}
		free(list_items);
		free(size);
	}
	stack *pile = Search_List(unit);
    DisplayStack(pile);
    FreeStack(pile);
    free(unit);
	return EXIT_SUCCESS;
}


