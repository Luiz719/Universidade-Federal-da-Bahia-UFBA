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
}

void Insert(list *unit, item *element, int pos){
    if(unit-> head == NULL){
		unit-> head = element;
		unit-> tail = element;
	}else{
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
}

int PopList(list *unit, int pos){
    if(unit-> head == NULL)
        return -99999;
    item *last_aux = unit-> head;
    int value, counter = 0;
    while(last_aux-> next != NULL && counter != pos - 1){
        last_aux = last_aux-> next;
        counter++;
    }
    if(pos == 0){
        item *aux = unit-> head;
        unit-> head = aux-> next;
        value = aux-> value;
        free(aux);
        return value;
    }
    if(last_aux-> next == NULL){
        unit-> tail = last_aux-> previous;
        last_aux-> previous-> next = NULL;
        value = last_aux-> value;
        free(last_aux);
        return value;
    }
    item *aux = last_aux-> next;
    last_aux-> next = aux-> next;
    if(last_aux-> next == NULL)
        unit-> tail = last_aux;
    if(aux-> next != NULL)
        aux-> next-> previous = last_aux;
    value = aux-> value;
    free(aux);
    return value;
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
	branch-> childs = (node**)malloc((max_keys + 2) * sizeof(node*));
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

void FreeNode(node *branch, int max_keys, int toggle){
    FreeList(branch-> value);
    //Determines if it is ok to free childs
    if(toggle)
        free(branch-> childs);
    free(branch);
}

//Fast Insertion
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
    partition *dualNode = (partition*)malloc(sizeof(partition));
    item *aux = branch-> value-> head;
    //Node with the smaller values
    dualNode-> node1 = NewNode(branch-> keys - 1);
    //Node with the bigger values
    dualNode-> node2 = NewNode(branch-> keys - 1);
    dualNode-> node1-> parent = branch-> parent;
    dualNode-> node2-> parent = branch-> parent;
    int counter = 0;
    //Determining the position of the median value
    int median = branch-> keys % 2 == 0? branch-> keys / 2 - 1: branch-> keys / 2;
    while(aux != NULL){
        if(counter < median)
            insertInNode(aux-> value, dualNode-> node1);
        else if(counter == median)
            dualNode-> median = aux-> value;
        else
            insertInNode(aux-> value, dualNode-> node2);
        counter++;
        aux = aux-> next;
    }
    FreeNode(branch, (branch-> keys - 1), 0);
    return dualNode;
}

void InsertionSort(int a, node *root){
    int counter = 0;
    item *aux = root-> value-> head;
    while(aux != NULL && a > aux-> value){
        aux = aux-> next;
        counter++;
    }
    Insert(root-> value, NewItem(a), counter);
    root-> keys += 1;
}

void Add_Aux(int a, node *root, Btree *tree){
    InsertionSort(a, root);
    //Dividing the node and sending the median upwards
    if(root-> keys > tree-> max_keys){
        node *copy = NewNode(tree-> max_keys);
        *copy = *root;
        partition *dualNode = DivideNode(root);
        if(!copy-> leaf){
            //If two or more nodes were divided in the same operation
            int median = copy-> keys % 2 == 0? copy-> keys / 2 - 1: copy-> keys / 2;
            int median2 = copy-> keys % 2 != 0? copy-> keys / 2 + 1: copy-> keys / 2;
            for(int i = 0; i <= copy-> keys; i++){
                if(i <= median){
                    dualNode-> node1-> childs[i] = copy-> childs[i];
                    dualNode-> node1-> childs[i]-> parent = dualNode-> node1;
                }else{
                    dualNode-> node2-> childs[i - median2] = copy-> childs[i];
                    dualNode-> node2-> childs[i - median2]-> parent = dualNode-> node2;
                }
            }
            dualNode-> node1-> leaf = 0;
            dualNode-> node2-> leaf = 0;
        }
        //Means that the tree will grow
        if(copy-> parent == NULL){
            //Creates a new node to be the tree's root
            tree-> root = insertInNode(dualNode-> median, NewNode(tree-> max_keys));
            tree-> root-> childs[0] = dualNode-> node1;
            tree-> root-> childs[1] = dualNode-> node2;
            dualNode-> node1-> parent = tree-> root;
            dualNode-> node2-> parent = tree-> root;
            tree-> root-> leaf = 0;
        }else{
            int keys = copy-> parent-> keys;
            //Finding the first child that is null
            int c = 0;
            while(copy-> parent-> childs[c]-> value != NULL){
                c++;
            }
            //Reallocating parent's childs pointers
            for(int i = keys + 1; i > c + 1; i--){
                copy-> parent-> childs[i] = copy-> parent-> childs[i-1];
            }
            copy-> parent-> childs[c] = dualNode-> node1;
            copy-> parent-> childs[c + 1] = dualNode-> node2;
            Add_Aux(dualNode-> median, copy-> parent, tree);
        }
        free(copy);
    }
}

void AddComplement(int a, node *branch, Btree *tree){
    if(branch-> leaf){
		Add_Aux(a, branch, tree);
	}else{
	    //Finding the correct branch
	    int counter = 0;
	    item *aux = branch-> value-> head;
        while(aux != NULL && a > aux-> value){
            aux = aux-> next;
            counter++;
        }
        //Untill a leaf is found
        AddComplement(a, branch-> childs[counter], tree);
	}
}

void Add(int a, Btree *tree){
	if(tree-> root == NULL){
		tree-> root = insertInNode(a, NewNode(tree-> max_keys));
	}else{
	    AddComplement(a, tree-> root, tree);
	}
}

int *FindNodesPos(int key, node *branch){
    int *nodesPos = (int*)calloc(sizeof(int), 3);
    if(branch-> parent != NULL){
        item *aux = branch-> parent-> value-> head;
        int nodePos = 0;
        int parentPos = 0;
        int brotherPos = 1;
        //Find the Nodes positions
        while(aux != NULL && key > aux-> value){
            aux = aux-> next;
            nodePos++;
            brotherPos = nodePos - 1;
            parentPos = nodePos - 1;
        }
        //0 = target Node; 1 = parent Node; 2 = target's brother Node
        nodesPos[0] = nodePos;
        nodesPos[1] = parentPos;
        nodesPos[2] = brotherPos;
    }
    return nodesPos;
}

void ConcatenateElements(int parentKey, node *target, int nodePos, int bPos){
    int newPos = nodePos < bPos? nodePos : bPos;
    node *aux = target-> parent;
    node *brother = aux-> childs[bPos];
    //Adding the brother node's list to the target
    if(newPos == nodePos)
        Insert_List(brother-> value, target-> value, target-> keys);
    else
        Insert_List(brother-> value, target-> value, 0);
    //Inserting the parent's key in the node
    InsertionSort(parentKey, target);
    target-> keys += brother-> keys;
    //Transferring the brother's childs to the target
    for(int i = 1; i < target-> keys + 1; i++){
        target-> childs[i] = brother-> childs[i - 1];
        if(target-> childs[i] != NULL)
            target-> childs[i]-> parent = target;
    }
    //Reallocating parent's childs pointers
    aux-> keys--;
    aux-> childs[newPos] = target;
    for(int i = newPos + 1; i < aux-> keys + 1; i++){
        aux-> childs[i] = aux-> childs[i + 1];
    }
    aux-> childs[aux-> keys + 1] = NULL;
    free(brother);
}

void Redistribute(node *branch, int nodePos, int bPos){
    node *aux = branch-> parent;
    if(nodePos > bPos){
        int temp = nodePos;
        nodePos = bPos;
        bPos = temp;
    }
    //Dividing the node and sending the median to the parent
    partition *dualNode = DivideNode(branch);
    insertInNode(dualNode-> median, aux);;
    aux-> childs[nodePos] = dualNode-> node1;
    aux-> childs[bPos] = dualNode-> node2;
}

void CheckTree(node *root, Btree *tree, int key){
    //Finding the parent's key that will be concatenated
    int *pos = FindNodesPos(key, root);
    int parentKey = PopList(root-> parent-> value, pos[1]);
    int nodeKey = pos[0];
    int brotherKey = pos[2];
    free(pos);
    ConcatenateElements(parentKey, root, nodeKey, brotherKey);
    //Redistribute the keys if necessary
    if(root-> keys > tree-> max_keys){
        Redistribute(root, nodeKey, brotherKey);
        return;
    }
    //Check parent's keys
    node *aux = root-> parent;
    if(aux != NULL && aux-> keys < tree-> max_keys / 2){
        //Means that the tree will shrink
        if(aux == tree-> root && aux-> keys == 0){
            tree-> root = root;
            FreeList(aux-> value);
            free(aux-> childs);
            free(aux);
            tree-> root-> parent = NULL;
        }else{
        //Parent will be concatenated with its respectively parent and brother
            key = root-> value-> tail-> value;
            CheckTree(aux, tree, key);
        }
    }
}

void RemoveNotLeaf(node *root, node *branch, int keyPos, Btree *tree){
    if(!root-> leaf){
        //Finding the rigtmost's value
        RemoveNotLeaf(root-> childs[root-> keys], branch, keyPos, tree);
    }else{
        //Replacing the key that will be removed with it
        int key = PopList(branch-> value, keyPos);
        branch-> keys--;
        InsertionSort(PopList(root-> value, root-> keys), branch);
        root-> keys--;
        if(root-> keys < tree-> max_keys / 2){
            CheckTree(root, tree, key);
        }
    }
}

void RemoveLeaf(int keyPos, node *root, Btree *tree){
    //Just remove and check
    int key = PopList(root-> value, keyPos);
    root-> keys--;
    if(root != tree-> root && root-> keys < tree-> max_keys / 2)
        CheckTree(root, tree, key);
}

void RemoveNode(int key, node *root, Btree *tree){
    if(root != NULL){
        int counter = 0;
        int found = 0;
        item *aux = root-> value-> head;
        //Searching the keys' node
        while(aux != NULL && key >= aux-> value && !found){
            if(aux-> value == key)
                found = 1;
            else{
                aux = aux-> next;
                counter++;
            }
        }
        if(!found)
            RemoveNode(key, root-> childs[counter], tree);
        else{
            if(root-> leaf)
                RemoveLeaf(counter, root, tree);
            else
                RemoveNotLeaf(root-> childs[counter], root, counter, tree);
        }
    }
}

//Selects Add[1] or Remove[0]
void AddOrRemove(int toggle, int key, Btree *tree){
    if(toggle)
        Add(key, tree);
    else
        RemoveNode(key, tree-> root, tree);
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

void DisplayAndCLearTree(node *root, Btree *tree){
	if(root != NULL){
		Display(root-> value);
		for(int i = 0; i < root-> keys + 1; i++){
		    if(root-> childs[i] != NULL)
	            DisplayAndCLearTree(root-> childs[i], tree);
		}
		FreeNode(root, tree-> max_keys, 1);
	}
}

int main(int argc, char **argv){
    int lines, max_keys, toggle, data;
    scanf("%d\n", &lines);
    int data_lines = lines - 1;
    scanf("%d\n", &max_keys);
    Btree *tree = NewTree(max_keys);
	for(int i = 0; i < data_lines; i++){
		scanf("%d %d\n", &toggle, &data);
		AddOrRemove(toggle, data, tree);
	}
	DisplayAndCLearTree(tree-> root, tree);
	free(tree);
	return EXIT_SUCCESS;
}

