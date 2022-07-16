#include <stdlib.h>
#include <stdio.h>

int prime(int a){
    int result = 1;
    if(a == 1)
        return 0;
    for(int i = 2; i <= a/2;i++){
        if(a % i == 0){
            result = 0;
            break;
        }
    }
    return result;
}

int main(){
    int lines, num;
    scanf("%d\n", &lines);
    for(int i = 0; i < lines; i++){
        scanf("%d", &num);
        printf("%d", prime(num));
    }
    return EXIT_SUCCESS;
}
