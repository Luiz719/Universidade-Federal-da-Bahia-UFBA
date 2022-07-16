#include <stdlib.h>
#include <stdio.h>

void fibonacci(int a){
    unsigned int last = 1, penultimate = 1, current = 0;
    for(int j = 0; j <= a; j++){
        if(j == 0 || j == 1){
            printf("1 ");
        }else{
            current = last + penultimate;
            printf("%u ", current);
            penultimate = last;
            last = current;
        }
    }
}

int main(){
    int lines, num;
    scanf("%d\n", &lines);
    for(int i = 0; i < lines; i++){
        scanf("%d", &num);
        fibonacci(num);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
