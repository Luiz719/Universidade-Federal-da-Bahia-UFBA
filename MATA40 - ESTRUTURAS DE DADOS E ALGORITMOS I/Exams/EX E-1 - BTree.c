#include <stdio.h>
#include <stdlib.h>

//Linked List
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
		unit-> tail-> next = element;
		element-> previous = unit-> tail;
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

int PopList(list *unit, int pos){
    if(unit-> head != NULL){
        item *last_aux = unit-> head;
        int value, counter = 0;
        while(last_aux-> next != NULL && counter != pos - 1){
            last_aux = last_aux-> next;
            counter++;
        }
        if(pos == 0){
            item *aux = unit-> head;
            unit-> head = aux-> next;
            aux-> previous = NULL;
            value = aux-> value;
            free(aux);
            return value;
        }else if(last_aux-> next == NULL){
            unit-> tail = last_aux-> previous;
            last_aux-> previous-> next = NULL;
            value = last_aux-> value;
            free(last_aux);
            return value;
        }else{
            item *aux = last_aux-> next;
            last_aux-> next = aux-> next;
            aux-> next-> previous = last_aux;
            value = aux-> value;
            free(aux);
            return value;
        }
    }else
	    return -99999;
}

void FreeList(list *unit){
    while(unit-> head != NULL){
        item *aux = unit-> head;
        unit-> head = aux-> next;
        free(aux);
    }
    free(unit);
}

//Btree
typedef struct node{
	list *value;
	struct node *parent;
	struct node **childs;
	int keys;
	int leaf;
}node;

typedef struct Btree{
	struct node *root;
	int max_keys;
}Btree;

Btree *NewTree(int keys){
	Btree *tree = (Btree*)malloc(sizeof(Btree));
	tree-> root = NULL;
	tree-> max_keys = keys;
	return tree;
}

node *NewNode(int max_keys){
	node *branch = (node*)malloc(sizeof(node));
	branch-> value = NewList();
	branch-> parent = NULL;
	branch-> childs = (node**)malloc((max_keys+2) * sizeof(node*));
    for(int i = 0; i <= max_keys + 1; i++)
	   branch-> childs[i] = NULL;
	branch-> keys = 0;
	branch-> leaf = 1;
	return branch;
}

void Free_vector(node **vector, int lines){
    for(int i = 0; i < lines; i++){
        free(vector[i]);
    }
    free(vector);
}

void FreeNode(node *branch, int max_keys){
    FreeList(branch-> value);
    free(branch);
}

node *insertInNode(int a, node *branch){
    Append(branch-> value, NewItem(a));
    branch-> keys += 1;
    return branch;
}

//Dividing a node in two new ones
typedef struct partition{
    struct node *node1;
    struct node *node2;
    int median;
}partition;

partition *DivideNode(node *branch){
    partition *dualnode = (partition*)malloc(sizeof(partition));
    item *aux = branch-> value-> head;
    dualnode-> node1 = NewNode(branch-> keys - 1);
    dualnode-> node2 = NewNode(branch-> keys - 1);
    dualnode-> node1-> parent = branch-> parent;
    dualnode-> node2-> parent = branch-> parent;
    int counter = 0;
    int median = branch-> keys % 2 == 0? branch-> keys / 2 - 1: branch-> keys / 2;
    while(aux != NULL){
        if(counter < median)
            insertInNode(aux-> value, dualnode-> node1);
        else if(counter == median)
            dualnode-> median = aux-> value;
        else
            insertInNode(aux-> value, dualnode-> node2);
        counter++;
        aux = aux-> next;
    }
    FreeNode(branch, (branch-> keys - 1));
    return dualnode;
}

void Add_Aux(int a, node *root, Btree *tree){
    //Insertion Sort like
    int counter = 0;
    item *aux = root-> value-> head;
    while(aux != NULL && a > aux-> value){
        aux = aux-> next;
        counter++;
    }
    Insert(root-> value, NewItem(a), counter);
    root-> keys += 1;
    //Dividing the node and send the median upwards
    if(root-> keys > tree-> max_keys){
        node *copy = NewNode(tree-> max_keys);
        *copy = *root;
        partition *dualnode = DivideNode(root);
        if(!copy-> leaf){
            //If two or more nodes were divided in the same operation
            int median = copy-> keys % 2 == 0? copy-> keys / 2 - 1: copy-> keys / 2;
            int median2 = copy-> keys % 2 != 0? copy-> keys / 2 + 1: copy-> keys / 2;
            for(int i = 0; i <= copy-> keys; i++){
                if(i <= median){
                    dualnode-> node1-> childs[i] = copy-> childs[i];
                    dualnode-> node1-> childs[i]-> parent = dualnode-> node1;
                }else{
                    dualnode-> node2-> childs[i - median2] = copy-> childs[i];
                    dualnode-> node2-> childs[i - median2]-> parent = dualnode-> node2;
                }
            }
            dualnode-> node1-> leaf = 0;
            dualnode-> node2-> leaf = 0;
        }
        if(copy-> parent == NULL){
            tree-> root = insertInNode(dualnode-> median, NewNode(tree-> max_keys));
            tree-> root-> childs[0] = dualnode-> node1;
            tree-> root-> childs[1] = dualnode-> node2;
            dualnode-> node1-> parent = tree-> root;
            dualnode-> node2-> parent = tree-> root;
            tree-> root-> leaf = 0;
        }else{
            dualnode-> node1-> parent = copy-> parent;
            dualnode-> node2-> parent = copy-> parent;
            int keys = copy-> parent-> keys;
            int c = 0;
            while(copy-> parent-> childs[c]-> value != NULL){
                c++;
            }
            for(int i = keys + 1; i > c + 1; i--){
                copy-> parent-> childs[i] = copy-> parent-> childs[i-1];
            }
            copy-> parent-> childs[c] = dualnode-> node1;
            copy-> parent-> childs[c + 1] = dualnode-> node2;
            Add_Aux(dualnode-> median, copy-> parent, tree);
        }
        free(copy);
    }
}

void AddComplement(int a, node *branch, Btree *tree){
    if(branch-> leaf){
		Add_Aux(a, branch, tree);
	}else{
	    int counter = 0;
	    item *aux = branch-> value-> head;
        while(aux != NULL && a > aux-> value){
            aux = aux-> next;
            counter++;
        }
        AddComplement(a, branch-> childs[counter], tree);
	}
}

void Add(int a, node *branch, Btree *tree){
	if(tree-> root == NULL){
		tree-> root = insertInNode(a, branch);
	}else{
	    AddComplement(a, tree-> root, tree);
	}
}

void DisplayTree(node *root){
	if(root != NULL){
		Display(root-> value);
		for(int i = 0; i < root-> keys + 1; i++){
	        if(root-> childs[i] != NULL){
                printf("%dth child = ", i);
	            DisplayTree(root-> childs[i]);
	        }
		}
	}
}

void BtreeSearch(int key, node *root){
    if(root != NULL){
        int counter = 0;
        int found = 0;
        item *aux = root-> value-> head;
        while(aux != NULL){
            printf("%d ", aux-> value);
            if(aux-> value == key)
                found = 1;
            if(key > aux-> value)
                counter++;
            aux = aux-> next;
        }
        if(!found)
            BtreeSearch(key, root-> childs[counter]);
    }
}

int main(int argc, char **argv){
    int lines, max_keys, key, data;
    scanf("%d\n", &lines);
    int data_lines = lines - 2;
    scanf("%d\n", &max_keys);
    Btree *tree = NewTree(max_keys);
    scanf("%d\n", &key);
	for(int i = 0; i < data_lines; i++){
		scanf("%d\n", &data);
		Add(data, NewNode(max_keys), tree);
	}
	BtreeSearch(key, tree-> root);
	free(tree);
	return EXIT_SUCCESS;
}

