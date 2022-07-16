#include <stdlib.h>
#include <stdio.h>

unsigned int multiples(int a){
    unsigned int sum = 0;
    for(int j = 1; j < a; j ++){
        if(j % 3 == 0 || j % 5 == 0){
            sum += j;
        }
    }
    return sum;
}

int main(){
    int lines, num;
    scanf("%d\n", &lines);
    for(int i = 0; i < lines; i++){
        scanf("%d", &num);
        printf("%u\n", multiples(num));
    }
    return EXIT_SUCCESS;
}
