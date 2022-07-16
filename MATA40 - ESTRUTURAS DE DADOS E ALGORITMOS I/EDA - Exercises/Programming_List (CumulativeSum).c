#include <stdlib.h>
#include <stdio.h>

void printv(double *p, int size){
    for(int i = 0; i < size; i++){
        printf("%.1lf ", p[i]);
    }
    printf("\n");
}

double *acc_sum(double *p, int size){
    double temp_item = 0;
    for(int i = 0; i < size; i++){
        if(i != 0){
            temp_item = p[i - 1];
            p[i] = p[i] + temp_item;

        }
    }
    return p;
}

int main(){
    int n;
    scanf("%d ", &n);
    int size[n];
    for(int i = 0; i < n; i++){
        scanf("%d ", &size[i]);
    }
    for(int i = 0; i < n; i++){
        double *p = (double*)malloc(sizeof(double) * size[i]);
        for(int j = 0; j < size[i]; j++){
            scanf("%lf ", &p[j]);
        }
        printv(acc_sum(p, size[i]), size[i]);
        free(p);
    }
    return EXIT_SUCCESS;
}

