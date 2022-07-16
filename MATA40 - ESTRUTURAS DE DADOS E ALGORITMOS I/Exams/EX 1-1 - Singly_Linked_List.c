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
	}else{
		item *aux = unit-> head;
		while(aux-> next != NULL)
			aux = aux-> next;
		aux-> next = element;
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
    }else{
        element-> next = aux-> next;
        aux-> next = element;
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
    item *first_aux = first_unit-> head;
    item *second_aux = second_unit-> head;
    int counter = 0;
    while(first_aux-> next != NULL && counter != pos - 1){
        first_aux = first_aux-> next;
        counter++;
    }
    while(second_aux-> next != NULL){
        second_aux = second_aux-> next;
    }
    if(pos == 0){
        second_aux-> next = first_unit-> head;
        first_unit-> head = second_unit->head;
    }else if(first_aux-> next == NULL){
        first_aux-> next = second_unit-> head;
    }else{
        second_aux-> next = first_aux-> next;
        first_aux-> next = second_unit-> head;
    }
}

void UniqueList(list *unit){
    item *aux = unit-> head;
    item *search_aux = aux;
    while(aux != NULL){
        item *garbage_aux;
        while(search_aux->next != NULL){
            if(aux-> value == search_aux-> next-> value){
                garbage_aux = search_aux-> next;
                search_aux-> next = search_aux-> next -> next;
                free(garbage_aux);
            }else{
                search_aux = search_aux-> next;
            }
        }
        aux = aux-> next;
        search_aux = aux;
    }
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
    int pos;
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
                Append(second_unit, NewItem(list_items[i]));
            else
                pos = list_items[i];
		}
		free(list_items);
		free(size);
	}
	Insert_List(second_unit, first_unit, pos);
	Display(first_unit);
	printf("\n");
	UniqueList(first_unit);
	Display(first_unit);
	FreeList(first_unit);
	return EXIT_SUCCESS;
}

