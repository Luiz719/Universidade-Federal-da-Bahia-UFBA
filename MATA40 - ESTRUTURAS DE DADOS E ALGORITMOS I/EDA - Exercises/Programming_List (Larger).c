#include <stdlib.h>
#include <stdio.h>

int larger(long int *p, int size){
    long int bigger = 0;
    int id_bigger = 0;
    for(int i = 0; i < size; i++){
        if(i == 0){
            bigger = p[i];
        }else if(p[i] > bigger){
            bigger = p[i];
            id_bigger = i;
        }
    }
    return id_bigger;
}

int main(){
    int size;
    scanf("%d\n", &size);
    long int *num = (long int*)malloc(sizeof(long int) * size);
    for(int i = 0; i < size; i++){
        scanf("%ld ", &num[i]);
    }
    printf("%d %ld", larger(num, size), num[larger(num, size)]);
    free(num);
    return EXIT_SUCCESS;
}

