#include <stdlib.h>
#include <stdio.h>

unsigned int integers(int a){
    unsigned int result = 0;
    for(int i = 1; i <= a; i++){
        result += i;
    }
    return result;
}

int main(){
    int lines, num;
    scanf("%d\n", &lines);
    for(int i = 0; i < lines; i++){
        scanf("%d", &num);
        printf("%u\n", integers(num));
    }
    return EXIT_SUCCESS;
}
