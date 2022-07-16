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
	struct item *previous;
}list;

list *NewList(){
	list *unit = (list*)malloc(sizeof(list));
	unit-> head = NULL;
	unit-> previous = NULL;
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
        unit-> head = element;
    }else if(aux-> next == NULL){
        aux-> next = element;
        element-> previous = aux;
    }else{
        element-> next = aux-> next;
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

list *Search_List(list *second_unit, list *first_unit){
    item *first_aux = first_unit-> head;
    item *second_aux = second_unit-> head;
    list *search_path = NewList();
    while(second_aux != NULL){
        if(second_aux-> value < first_aux-> value){
            while(first_aux-> previous != NULL){
                Append(search_path, NewItem(first_aux-> value));
                if(second_aux-> value >= first_aux-> value){
                    break;
                }
                first_aux = first_aux-> previous;
            }
            if(first_aux-> previous == NULL)
                Append(search_path, NewItem(first_aux-> value));
        }else if(second_aux-> value > first_aux-> value){
            while(first_aux-> next != NULL){
                Append(search_path, NewItem(first_aux-> value));
                if(second_aux-> value <= first_aux-> value){
                    break;
                }
                first_aux = first_aux-> next;
            }
            if(first_aux-> next == NULL)
                Append(search_path, NewItem(first_aux-> value));
        }else{
            Append(search_path, NewItem(first_aux-> value));
        }
        second_aux = second_aux-> next;
    }
    return search_path;
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
    list *first_unit = NewList();
    list *second_unit = NewList();
    list *search_path;
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
                Append(first_unit, NewItem(list_items[i]));
            else if(j == 1)
                Append(second_unit, NewItem(list_items[i]));;
		}
		free(list_items);
		free(size);
	}
	search_path = Search_List(second_unit, first_unit);
	Display(search_path);
	FreeList(first_unit);
	FreeList(search_path);
	return EXIT_SUCCESS;
}

