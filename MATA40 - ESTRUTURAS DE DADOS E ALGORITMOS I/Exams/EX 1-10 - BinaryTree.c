#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int value;
	int degrees;
	struct node *left;
	struct node *right;
	struct node *parent;
}node;

typedef struct binarytree{
	struct node *root;
}binarytree;

node *NewNode(int a){
	node *branch = (node*)malloc(sizeof(node));
	branch-> value = a;
	branch-> left = NULL;
	branch-> right = NULL;
	branch-> parent = NULL;
	branch-> degrees = 0;
	return branch;
}

binarytree * NewTree(){
	binarytree *tree = (binarytree*)malloc(sizeof(binarytree));
	tree-> root = NULL;
	return tree;
}

int NodeHeight(node *root){
    if(root == NULL)
        return 0;
    if(root-> left == NULL && root-> right == NULL)
        return 0;
    int left_path = NodeHeight(root-> left);
    int right_path = NodeHeight(root-> right);
    return 1 + ((left_path > right_path)? left_path : right_path);
}

int LevelOfNode(node *root){
    if(root-> parent == NULL)
        return 0;
    return 1 + LevelOfNode(root-> parent);
}

int LevelsCompleted (node *root){
     if(root-> left != NULL && root-> right != NULL){
        if(root-> left-> degrees == 0 && root-> right-> degrees == 0)
            return 1;
        int left_path = LevelsCompleted(root-> left);
        int right_path = LevelsCompleted(root-> right);
        return 1 + ((left_path < right_path)? left_path : right_path);
    }
    return 0;
}

void Add_Aux(node *branch, node *root){
    if(root-> left == NULL){
        root-> left = branch;
        branch-> parent = root;
        branch-> parent-> degrees += 1;
    }else if(root-> right == NULL){
        root-> right = branch;
        branch-> parent = root;;
        branch-> parent-> degrees += 1;
    }else{
        if(root-> left-> degrees != 2){
            Add_Aux(branch, root-> left);
        }else if(root-> right-> degrees != 2){
            Add_Aux(branch, root-> right);
        }else{
            if(LevelsCompleted(root-> left) <= LevelsCompleted(root-> right))
                Add_Aux(branch, root-> left);
            else
                Add_Aux(branch, root-> right);
        }
    }
}

void Add(node *branch, binarytree *tree){
	if(tree-> root == NULL){
		tree-> root = branch;
	}else{
		Add_Aux(branch, tree-> root);
	}
}

void Remove_Aux(node *root, node *remove_aux){
    while(root-> left != NULL){
        root = root-> left;
    }
    if(root-> degrees == 0){
        if(root-> parent != NULL){
            if(root-> parent-> left != NULL){
                root-> parent-> left = NULL;
            }else if(root-> parent-> right != NULL){
                root-> parent-> right = NULL;
            }
            root-> parent-> degrees -= 1;
        }
        *remove_aux = *root;
        free(root);
    }else if(root-> right != NULL){
        Remove_Aux(root-> right, remove_aux);
    }
}

int RemoveLeftmostLeaf(binarytree *tree){
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

void ClearTree(binarytree *tree){
	while(tree-> root != NULL){
		RemoveLeftmostLeaf(tree);
	}
	free(tree);
}

void DisplayAndClearTree(binarytree *tree){
	while(tree-> root != NULL){
		printf("%d ", RemoveLeftmostLeaf(tree));
	}
	printf("\n");
}

void Search_Aux(node *root, int a, node *aux, int b, node *aux_b){
    if(root != NULL){
		if(root-> value == a)
		    *aux = *root;
		if(root-> value == b)
		    *aux_b = *root;
		Search_Aux(root->left, a, aux, b, aux_b);
		Search_Aux(root->right, a, aux, b, aux_b);
	}
}

void SearchTree(binarytree *tree, int a, int b){
    node *aux_a = NewNode(-999999);
    node *aux_b = NewNode(-999999);
    Search_Aux(tree-> root, a, aux_a, b, aux_b);
    if(aux_a-> value != a && aux_b-> value != b){
        printf("%d\n", NodeHeight(tree-> root));
    }else if(aux_a-> value != a){
        printf("%d\n", NodeHeight(aux_b));
    }else if(aux_b-> value != b){
        printf("%d\n", NodeHeight(aux_a));
    }else{
        int a_level = LevelOfNode(aux_a);
        int b_level = LevelOfNode(aux_b);
        int difference = (a_level >= b_level)? a_level - b_level:
                           b_level - a_level;
        printf("%d\n", difference);
    }
    free(aux_a);
    free(aux_b);
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
	binarytree *tree = NewTree();
	int a, b;
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
		        Add(NewNode(list_items[i]), tree);
		    else if(i == 0)
		        a = list_items[i];
		    else
		        b = list_items[i];
		}
		if(j != 0)
		    SearchTree(tree, a, b);
		free(list_items);
		free(size);
	}
	ClearTree(tree);
	return EXIT_SUCCESS;
}

