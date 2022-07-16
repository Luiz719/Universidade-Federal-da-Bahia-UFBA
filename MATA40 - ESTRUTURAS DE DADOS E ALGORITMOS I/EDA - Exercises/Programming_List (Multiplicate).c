#include <stdlib.h>
#include <stdio.h>

int mult(int a, int b){
    int result = 0;
    for(int i = 0;i < b;i++)
        result += a;
    return result;
}

int main(){
    int lines, num1, num2;
    scanf("%d\n", &lines);
    for(int i = 0; i < lines; i++){
        scanf("%d %d", &num1, &num2);
        printf("%d", mult(num1, num2));
    }
    return EXIT_SUCCESS;
}
