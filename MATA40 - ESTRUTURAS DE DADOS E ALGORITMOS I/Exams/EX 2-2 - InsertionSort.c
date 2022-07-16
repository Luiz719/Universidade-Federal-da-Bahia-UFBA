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
    printf("\n");
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

list *partialInsertionSort(list *unit, int a){
    list *sorted_unit = NewList();
    item *aux = unit-> head;
    int counter = 1;
    while(aux-> next != NULL && counter <= a){
        if(sorted_unit-> head == NULL)
            Append(sorted_unit, NewItem(aux-> value));
        else{
            item *compare_aux = sorted_unit-> head;
            while(compare_aux-> next != NULL)
                compare_aux = compare_aux-> next;
            int pos = counter - 1;
            while(compare_aux != NULL && compare_aux-> value > aux-> value){
                compare_aux = compare_aux-> previous;
                pos--;
            }
            Insert(sorted_unit, NewItem(aux-> value), pos);
        }
        aux = aux-> next;
        counter++;
    }
    return sorted_unit;
}

int main(int argc, char **argv){
    list *unit = NewList();
    list *sorted_unit;
    int lines, max_it, data;
    scanf("%d\n", &lines);
    scanf("%d\n", &max_it);
	for(int i = 0; i < lines - 1; i++){
		scanf("%d\n", &data);
		Append(unit, NewItem(data));
	}
	sorted_unit = partialInsertionSort(unit, max_it);
	Display(sorted_unit);
	FreeList(unit);
	FreeList(sorted_unit);
	return EXIT_SUCCESS;
}

