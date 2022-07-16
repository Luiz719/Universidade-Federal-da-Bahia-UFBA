#include <stdlib.h>
#include <stdio.h>

long int factorial(int a){
    long int result = 1;
    for(int i = a; i >= 2;i--){
        result *= i;
    }
    return result;
}

int main(){
    int lines, num;
    scanf("%d\n", &lines);
    for(int i = 0; i < lines; i++){
        scanf("%d", &num);
        printf("%ld\n", factorial(num));
    }
    return EXIT_SUCCESS;
}
