#include <stdlib.h>
#include <stdio.h>

double mean(double *p, int size){
    double sum, result;
    for(int i = 0; i < size; i++){
        sum += p[i];
    }
    result = sum/size;
    return result;
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
        printf("%.1lf\n", mean(num, arr[i]));
        free(num);
    }
    return EXIT_SUCCESS;
}

