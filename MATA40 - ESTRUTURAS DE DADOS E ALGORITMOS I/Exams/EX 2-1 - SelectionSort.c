#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
	int value;
	struct item *next;
	struct item *previous;
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
	element-> previous = NULL;
	return element;
}

void Append(list *unit, item *element){
	if(unit-> head == NULL){
		unit-> head = element;
	}else{
		item *aux = unit-> head;
		while(aux-> next != NULL)
			aux = aux-> next;
		aux-> next = element;
		element-> previous = aux;
	}
}

void Display(list *unit){
	item *aux = unit-> head;
    while(aux != NULL){
        printf("%d ", aux-> value);
        aux = aux-> next;
    }
}

void Insert(list *unit, item *element, int pos){
    item *aux = unit-> head;
    int counter = 0;
    while(aux-> next != NULL && counter != pos - 1){
        aux = aux-> next;
        counter++;
    }
    if(pos == 0){
        element-> next = unit-> head;
        unit-> head-> previous = element;
        unit-> head = element;
    }else if(aux-> next == NULL){
        aux-> next = element;
        element-> previous = aux;
    }else{
        element-> next = aux-> next;
        element-> next-> previous = element;
        aux-> next = element;
        element-> previous = aux;
    }
}

void FreeList(list *unit){
    while(unit-> head != NULL){
        item *aux = unit-> head;
        unit-> head = aux-> next;
        free(aux);
    }
    free(unit);
}

void partialSelectionSort(list *unit, int a){
    item *aux = unit-> head;
    int smaller = 0;
    int counter = 1;
    while(aux-> next != NULL && counter <= a){
        smaller = aux-> value;
        item *compare_aux = aux->next;
        item *target = aux;
        while(compare_aux != NULL){
            if(compare_aux-> value < smaller){
                smaller = compare_aux-> value;
                target = compare_aux;
            }
            compare_aux = compare_aux-> next;
        }
        if(aux != target){
            //Making a copy of the aux item
            item *temp = NewItem(0);
            *temp = *aux;
            if(aux == unit-> head){
                unit-> head = target;
            }else{
                temp-> previous-> next = target;
            }
            //Placing the aux in the target location
            aux-> next = target-> next;
            if(target-> next != NULL)
                target-> next-> previous = aux;
            if(target-> previous != aux){
                aux-> previous = target-> previous;
                target-> previous-> next = aux;
                target-> next = temp-> next; //*
            }else{
                aux-> previous = target;
                target-> next = aux; //*
            }
            //*Placing the target in the aux location
            target-> previous = temp-> previous;
            target-> next-> previous = target;
            free(temp);
        }
        aux = target-> next;
        counter++;
    }
}

int main(int argc, char **argv){
    list *unit = NewList();
    int lines, max_it, data;
    scanf("%d\n", &lines);
    scanf("%d\n", &max_it);
	for(int i = 0; i < lines - 1; i++){
		scanf("%d\n", &data);
		Append(unit, NewItem(data));
	}
	partialSelectionSort(unit, max_it);
	Display(unit);
	FreeList(unit);
	return EXIT_SUCCESS;
}

