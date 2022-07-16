#include <stdlib.h>
#include <stdio.h>

int division(int a, int b){
    int result = 0;
    while(a >= b && a > 0){
        a -= b;
        result++;
    }
    return result;
}

int main(){
    int lines, num1, num2;
    scanf("%d\n", &lines);
    for(int i = 0; i < lines; i++){
        scanf("%d %d", &num1, &num2);
        printf("%d", division(num1, num2));
    }
    return EXIT_SUCCESS;
}
