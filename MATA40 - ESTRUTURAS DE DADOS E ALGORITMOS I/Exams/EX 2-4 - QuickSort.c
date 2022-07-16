#include <stdio.h>
#include <stdlib.h>

typedef struct item{
	int value;
	struct item *next;
	struct item *previous;
}item;

typedef struct list{
	struct item *head;
	struct item *tail;
}list;

list *NewList(){
	list *unit = (list*)malloc(sizeof(list));
	unit-> head = NULL;
	unit-> tail = NULL;
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
	unit-> tail = element;
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
        unit-> tail = element;
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

void Insert_List(list *second_unit, list *first_unit, int pos){
    if(first_unit-> head == NULL){
        first_unit-> head = second_unit-> head;
        first_unit-> tail = second_unit-> tail;
    }else{
        item *first_aux = first_unit-> head;
        int counter = 0;
        while(first_aux-> next != NULL && counter != pos - 1){
            first_aux = first_aux-> next;
            counter++;
        }
        if(pos == 0){
            second_unit-> tail-> next = first_unit-> head;
            first_unit-> head-> previous = second_unit-> tail;
            first_unit-> head = second_unit->head;
        }else if(first_aux-> next == NULL){
            first_aux-> next = second_unit-> head;
            second_unit-> head-> previous = first_aux;
            first_unit-> tail = second_unit-> tail;
        }else{
            second_unit-> tail-> next = first_aux-> next;
            first_aux-> previous = second_unit-> tail;
            first_aux-> next = second_unit-> head;
            second_unit-> head-> previous = first_aux;
        }
    }
    free(second_unit);
}

list *ConcatenateElements(list *first_unit, list *second_unit, item *element){
    list *full_list = NewList();
    if(first_unit-> head == NULL){
        full_list-> head = element;
        element-> next = second_unit-> head;
        second_unit-> head-> previous = element;
        full_list-> tail = second_unit-> tail;
    }else if(second_unit-> head == NULL){
        full_list-> head = first_unit-> head;
        first_unit-> tail-> next = element;
        element-> previous = first_unit-> tail;
        full_list-> tail = element;
    }else{
        full_list-> head = first_unit-> head;
        first_unit-> tail-> next = element;
        element-> previous = first_unit-> tail;
        element-> next = second_unit-> head;
        second_unit-> head-> previous = element;
        full_list-> tail = second_unit-> tail;
    }
    free(first_unit);
    free(second_unit);
    return full_list;
}

//External Sorting
list *QuickSort(list *unit, int pivot_pos, int display_pivot){
    list *sorted_list = NewList();
    item *pivot = unit-> head;
    //Selecting pivot
    int counter = 0;
    while(counter < pivot_pos){
        pivot = pivot-> next;
        counter++;
    }
    //Partition of the set
    item *aux = unit-> head;
    list *left = NewList();
    list *right = NewList();
    while(aux != NULL){
        if(aux-> value <= pivot-> value && pivot != aux)
            Append(left, NewItem(aux-> value));
        else if(aux-> value > pivot-> value)
            Append(right, NewItem(aux-> value));
        aux = aux-> next;
    }
    if(display_pivot){
        if(left-> head != NULL)
            printf("%d ", left-> head-> value);
        if(right-> head != NULL)
            printf("%d ", right-> head-> value);
    }
    if(left-> head != NULL && left-> head != left-> tail)
        left = QuickSort(left, 0, 0);
    if(right-> head != NULL && right-> head != right-> tail)
        right = QuickSort(right, 0, 0);
    //Concatenating the lists
    item *new_pivot = NewItem(pivot-> value);
    sorted_list = ConcatenateElements(left, right, new_pivot);
    return sorted_list;
}

int main(int argc, char **argv){
    list *unit = NewList();
    list *sorted_list;
    int lines, pivot_pos, data;
    scanf("%d\n", &lines);
    scanf("%d\n", &pivot_pos);
	for(int i = 0; i < lines - 1; i++){
		scanf("%d\n", &data);
		Append(unit, NewItem(data));
	}
	sorted_list = QuickSort(unit, pivot_pos, 1);
	Display(sorted_list);
	FreeList(unit);
	FreeList(sorted_list);
	return EXIT_SUCCESS;
}

