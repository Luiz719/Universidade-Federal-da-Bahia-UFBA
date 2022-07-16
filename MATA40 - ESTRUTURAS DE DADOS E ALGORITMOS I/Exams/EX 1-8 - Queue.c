#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
	int value;
	struct item *next;
}item;

typedef struct queue{
	struct item *first;
	struct item *last;
	int size;
}queue;

item *NewItem(int a){
	item *element = (item*)malloc(sizeof(item));
	element-> value = a;
	element-> next = NULL;
	return element;
}

queue *NewQueue(){
	queue *row = (queue*)malloc(sizeof(queue));
	row-> first = NULL;
	row-> last = NULL;
	row-> size = 0;
	return row;
}

int queueIsEmpty(queue *row){
    if(row-> size == 0)
        return 1;
    return 0;
}

void Append(item *element, queue *row){
    if(queueIsEmpty(row)){
        row-> first = element;
        row-> last = element;
    }else{
        row-> last-> next = element;
        row-> last = element;
    }
	row-> size += 1;
}

item *Pop(queue *row){
    if(row-> first != NULL){
        item *aux = row-> first;
        row-> first = aux-> next;
        row-> size -= 1;
        aux-> next = NULL;
        return aux;
	}
	return NULL;
}

void Display(queue *row){
    item *aux = row-> first;
    while(aux != NULL){
        printf("%d ", aux-> value);
        aux = aux-> next;
    }
    printf("\n");
}

void FreeQueue(queue *row){
    while(row-> first != NULL){
        free(Pop(row));
    }
    free(row);
}

queue *DivideQueue(queue *row, int *pos){
    queue *priority_row = NewQueue();
    queue *aux_row = NewQueue();
    int counter = 1;
    while(row-> first != NULL){
        if(row-> first-> value >= 60 || row-> first-> value <= 5
           || counter == *pos){
            Append(Pop(row), priority_row);
            if(counter == *pos)
                pos++;
        }else
            Append(Pop(row), aux_row);
        counter++;
    }
    while(aux_row-> first != NULL){
        Append(Pop(aux_row), row);
    }
    return priority_row;
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
    queue *row = NewQueue();
    queue *priority_row;
    int *pos;
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
		    if(!j)
                Append(NewItem(list_items[i]), row);
		}
		if(!j)
		    free(list_items);
	    else
		    pos = list_items;
		free(size);
	}
	priority_row = DivideQueue(row, pos);
	Display(row);
	Display(priority_row);
	FreeQueue(priority_row);
	FreeQueue(row);
	free(pos);
	return EXIT_SUCCESS;
}

