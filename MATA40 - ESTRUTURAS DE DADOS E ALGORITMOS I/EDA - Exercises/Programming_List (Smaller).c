#include <stdlib.h>
#include <stdio.h>

int smaller(double *p, int size){
    double minor;
    int id_minor = 0;
    for(int i = 0; i < size; i++){
        if(i == 0){
            minor = p[i];
        }else if(p[i] < minor){
            minor = p[i];
            id_minor = i;
        }
    }
    return id_minor;
}

int main(){
    int lines;
    scanf("%d ", &lines);
    int arr[lines];
    for(int i = 0; i < lines; i++){
        scanf("%d ", &arr[i]);
    }
    for(int i = 0; i < lines; i++){
        double *num = (double*)malloc(sizeof(double) * arr[i]);
        for(int j = 0; j < arr[i]; j++){
            scanf("%lf ", &num[j]);
        }
        printf("%d %.1lf\n", smaller(num, arr[i]), num[smaller(num, arr[i])]);
        free(num);
    }
    return EXIT_SUCCESS;
}

