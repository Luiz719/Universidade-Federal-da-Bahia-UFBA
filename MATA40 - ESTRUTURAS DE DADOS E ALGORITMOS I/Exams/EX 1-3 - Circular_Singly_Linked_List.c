#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
	int value;
	char *name;
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

item *NewItem(char *name, int a){
	item *element = (item*)malloc(sizeof(item));
	element-> value = a;
	element-> name = name;
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
        printf("%s %d\n", aux->name, aux-> value);
        aux = aux-> next;
    }
    printf("%s %d\n", aux->name, aux-> value);
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

void Search_List(list *unit, char *person){
    item *aux = unit-> head;
    item *name_aux;
    int sum_aux = 0, counter = 0;
    do{
        if(!strcmp(aux-> name, person)){
            name_aux = aux;
        }
        sum_aux += aux-> value;
        aux = aux-> next;
    }while(aux != unit-> head);
    while(counter != sum_aux){
        name_aux = name_aux-> next;
        counter++;
    }
    printf("%s\n", name_aux->name);
}

void Free_vector(char **vector, int lines){
    for(int i = 0; i < lines; i++){
        free(vector[i]);
    }
    free(vector);
}

int main(int argc, char **argv){
    list *unit = NewList();
    char *person = (char*)malloc(15 * sizeof(char));
    char *aux;
	int total_lines, number;
	char** names = (char**)malloc(sizeof(char*) * total_lines);
	scanf("%d\n", &total_lines);
	for(int j = 0; j < total_lines - 1; j++){
	    names[j] = (char*)malloc(15 * sizeof(char));
		scanf("%s %d", names[j], &number);
		aux = names[j];
        Append(unit, NewItem(aux, number));
	}
    scanf("%s", person);
	Search_List(unit, person);
	FreeList(unit);
	Free_vector(names, total_lines);
	free(person);
	free(aux);
	return EXIT_SUCCESS;
}

