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

//Início de pilhas
typedef struct stack{
	struct item *top;
	int size;
}stack;

stack *NewStack(){
	stack *pile = (stack*)malloc(sizeof(stack));
	pile-> top = NULL;
	pile-> size = 0;
	return pile;
}

void Push(item *element, stack *pile){
	element-> next = pile->top;
	pile-> top = element;
	pile-> size += 1;
}

item *PopStack(stack *pile){
    if(pile-> top != NULL){
        item *aux = pile-> top;
        pile-> top = aux-> next;
        pile-> size -= 1;
        aux-> next = NULL;
        return aux;
	}
	return NULL;
}

void DisplayStack(stack *pile){
    item *aux = pile-> top;
    int print[pile-> size];
    int counter = 0;
    while(aux != NULL){
        print[counter] = aux-> value;
        aux = aux-> next;
        counter++;
    }
    for(int i = pile-> size - 1; i >= 0; i--)
        printf("%d ", print[i]);
    printf("\n");
}

void FreeStack(stack *pile){
    while(pile-> top != NULL){
        free(PopStack(pile));
    }
    free(pile);
}
//Fim de pilhas
//Início de árvores
typedef struct node{
	int value;
	int degrees;
	struct node *left;
	struct node *middle;
	struct node *right;
	struct node *parent;
}node;

typedef struct degree3tree{
	struct node *root;
}degree3tree;

node *NewNode(int a){
	node *branch = (node*)malloc(sizeof(node));
	branch-> value = a;
	branch-> left = NULL;
	branch-> middle = NULL;
	branch-> right = NULL;
	branch-> parent = NULL;
	branch-> degrees = 0;
	return branch;
}

degree3tree * NewTree(){
	degree3tree *tree = (degree3tree*)malloc(sizeof(degree3tree));
	tree-> root = NULL;
	return tree;
}

int LevelsCompleted (node *root){
     if(root-> left != NULL && root-> middle != NULL && root-> right != NULL){
        if(root-> left-> degrees == 0 && root-> right-> degrees == 0)
            return 1;
        int left_path = LevelsCompleted(root-> left);
        int middle_path = LevelsCompleted(root-> middle);
        int mix_path = (left_path < middle_path)? left_path : middle_path;
        int right_path = LevelsCompleted(root-> right);
        return 1 + ((mix_path < right_path)? mix_path : right_path);
    }
    if(root-> degrees > 0 && root-> degrees <= 3)
        return 0;
    else
        return 0;
}

void Add_Aux(node *branch, node *root){
    if(root-> left == NULL){
        root-> left = branch;
        branch-> parent = root;
        branch-> parent-> degrees += 1;
    }else if(root-> middle == NULL){
        root-> middle = branch;
        branch-> parent = root;
        branch-> parent-> degrees += 1;
    }else if(root-> right == NULL){
        root-> right = branch;
        branch-> parent = root;
        branch-> parent-> degrees += 1;
    }else{
        int left_path = LevelsCompleted(root-> left);
        int middle_path = LevelsCompleted(root-> middle);
        int right_path = LevelsCompleted(root-> right);
        if(left_path == middle_path && left_path == right_path)
            Add_Aux(branch, root-> left);
        else if(middle_path <= right_path)
            Add_Aux(branch, root-> middle);
        else
            Add_Aux(branch, root-> right);
    }
}

void Add(node *branch, degree3tree *tree){
	if(tree-> root == NULL){
		tree-> root = branch;
	}else{
		Add_Aux(branch, tree-> root);
	}
}

void Remove_Aux(node *root, node *remove_aux){
    node *aux = root;
    while(aux-> left != NULL){
        aux = aux-> left;
    }
    if(aux-> degrees == 0){
        if(aux-> parent != NULL){
            if(aux-> parent-> left != NULL){
                aux-> parent-> left = NULL;
            }else if(aux-> parent-> middle != NULL){
                aux-> parent-> middle = NULL;
            }else if(aux-> parent-> right != NULL){
                aux-> parent-> right = NULL;
            }
            aux-> parent-> degrees -= 1;
        }
        *remove_aux = *aux;
        free(aux);
    }else if(aux-> middle != NULL){
        Remove_Aux(aux-> middle, remove_aux);
    }else if(aux-> right != NULL){
        Remove_Aux(aux-> right, remove_aux);
    }
}

int RemoveLeftmostLeaf(degree3tree *tree){
    if(tree-> root == NULL)
        return -999;
    int value;
    int root = tree-> root-> value;
    node *remove_aux = NewNode(0);
    Remove_Aux(tree-> root, remove_aux);
    if(remove_aux-> value == root)
        tree-> root = NULL;
    value = remove_aux-> value;
    free(remove_aux);
    return value;
}

void DisplayAndClearTree(degree3tree *tree){
	while(tree-> root != NULL){
		printf("%d ", RemoveLeftmostLeaf(tree));
	}
	printf("\n");
}
//Fim de árvores

degree3tree **TreeFromADTs(queue *row, stack *pile){
    degree3tree **trees = (degree3tree**)malloc(sizeof(degree3tree*) * 2);
    degree3tree *queue_tree = NewTree();
    degree3tree *pile_tree = NewTree();
    int pile_value, queue_value;
    while(pile-> top != NULL){
        item *aux = PopStack(pile);
        item *aux2 = Pop(row);
        pile_value = aux-> value;
        queue_value = aux2-> value;
        free(aux);
        free(aux2);
        Add(NewNode(queue_value), queue_tree);
        Add(NewNode(pile_value), pile_tree);
    }
    trees[0] = queue_tree;
    trees[1] = pile_tree;
    return trees;
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
	degree3tree **trees;
    queue *row = NewQueue();
    stack *pile = NewStack();
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
		    Push(NewItem(list_items[i]), pile);
            Append(NewItem(list_items[i]), row);
		}
		free(list_items);
		free(size);
	}
	trees = TreeFromADTs(row, pile);
	DisplayAndClearTree(trees[0]);
	DisplayAndClearTree(trees[1]);
	free(trees[0]);
	free(trees[1]);
	free(trees);
	free(row);
	free(pile);
	return EXIT_SUCCESS;
}

