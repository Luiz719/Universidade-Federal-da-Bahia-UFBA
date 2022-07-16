#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Linked List
typedef struct item{
	char *value;
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

item *NewItem(char *data){
	item *element = (item*)malloc(sizeof(item));
	element-> value = data;
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
        printf("%s ", aux-> value);
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

//Hash
typedef struct hash{
    list **items;
    int size;
    int max_size;
}hash;

hash *NewHash(int max){
	hash *unit = (hash*)malloc(sizeof(hash));
	unit-> items = (list**)malloc(max * sizeof(list*));
	for(int i = 0; i < max; i++)
	    unit-> items[i] = NewList();
	unit-> size = 0;
	unit-> max_size = max;
	return unit;
}

int WordEncoder(char *data, int max){
    int sum = 0;
    for(int i = 0; i < strlen(data); i++){
        sum += data[i] - 96;
    }
    return sum % max;
}

void HashInsert(hash *unit, char *item){
    int pos = WordEncoder(item, unit-> max_size);
    Append(unit-> items[pos], NewItem(item));
	unit-> size += 1;
}

void DisplayHash(hash *unit){
    int iterations = unit-> size < unit-> max_size? unit-> size: unit-> max_size;
	for(int i = 0; i < iterations; i++){
		Display(unit-> items[i]);
	}
	printf("\n");
}

void FreeHash(hash *unit){
    for(int i = 0; i < unit-> max_size; i++)
	    FreeList(unit-> items[i]);
	free(unit-> items);
    free(unit);
}

void Search(hash *unit, int pos){
    item *aux = unit-> items[pos]-> head;
    if(aux != NULL){
        while(aux != NULL){
            printf("%s ", aux-> value);
            aux = aux-> next;
        }
    }
    printf("\n");
}

void Free_vector(char **vector, int lines){
    for(int i = 0; i < lines; i++){
        free(vector[i]);
    }
    free(vector);
}

int main(int argc, char **argv){
    int lines, max_size, pos;
    scanf("%d\n", &lines);
    int data_lines = lines - 2;
    char** data = (char**)malloc(sizeof(char*) * data_lines);
    scanf("%d\n", &max_size);
    hash *unit = NewHash(max_size);
    scanf("%d\n", &pos);
	for(int i = 0; i < data_lines; i++){
	    data[i] = (char*)malloc(30 * sizeof(char));
		scanf("%s\n", data[i]);
		HashInsert(unit, data[i]);
	}
	Search(unit, pos);
	FreeHash(unit);
	Free_vector(data, data_lines);
	return EXIT_SUCCESS;
}

