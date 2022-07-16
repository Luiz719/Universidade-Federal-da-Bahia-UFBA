#include <stdlib.h>
#include <stdio.h>

double intersection(double *p, double *q, int p_size, int q_size){
    double temp_item, sum_inter = 0;
    for(int i = 0; i < p_size; i++){
        for(int j = 0; j < q_size; j++){
            if(p[i] == q[j]){
                temp_item = p[i];
                q[j] = 0;
            }
        }
        sum_inter += temp_item;
        temp_item = 0;
    }
    return sum_inter;
}

int main(){
    int size1, size2;
    scanf("%d %d", &size1, &size2);
    double *p = (double*)malloc(sizeof(double) * size1);
    double *q = (double*)malloc(sizeof(double) * size2);
    for(int i = 0; i < size1; i++){
        scanf("%lf ", &p[i]);
    }
    for(int i = 0; i < size2; i++){
        scanf("%lf ", &q[i]);
    }
    printf("%.1lf", intersection(p, q, size1, size2));
    free(p);
    free(q);
    return EXIT_SUCCESS;
}

