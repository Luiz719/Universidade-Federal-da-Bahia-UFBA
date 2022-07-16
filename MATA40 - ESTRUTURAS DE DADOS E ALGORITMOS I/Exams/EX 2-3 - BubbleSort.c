#include <stdio.h>
#include <stdlib.h>

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

void SwitchItems(list *unit, item *aux, item *target){
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
    aux-> previous = target;
    //*Placing the target in the aux location
    target-> next = aux;
    target-> previous = temp-> previous;
    free(temp);
}

void partialBubbleSort(list *unit, int a){
    item *aux = NULL;
    int counter = 1;
    if(a != 0){
        do{
            item *compare_aux = unit-> head;
            while(compare_aux-> next != aux){
                if(compare_aux-> value > compare_aux-> next-> value){
                    SwitchItems(unit, compare_aux, compare_aux-> next);
                }else
                    compare_aux = compare_aux-> next;
            }
            aux = compare_aux;
            counter++;
        }while(aux != unit-> head-> next && counter <= a);
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
	partialBubbleSort(unit, max_it);
	Display(unit);
	FreeList(unit);
	return EXIT_SUCCESS;
}

