#include <stdlib.h>
#include <stdio.h>

double **create_matrix(int lines, int columns){
    double **matrix = (double**)malloc(sizeof(double*) * lines);
    for(int i = 0; i < lines; i++){
        matrix[i] = (double*)malloc(sizeof(double) * columns);
    }
    return matrix;
}

void lib_matrix(double **matrix, int lines, int columns){
    for(int i = 0; i < lines; i++){
        free(matrix[i]);
    }
    free(matrix);
}

double sum_diagonal(double **p, int lines, int columns){
    double sum = 0;
    for(int j = 0; j < lines; j++){
        sum += p[j][j];
    }
    return sum;
}

int main(){
    int lines, columns;
    scanf("%d %d", &lines, &columns);
    double **matrix = create_matrix(lines, columns);
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            scanf("%lf ", &matrix[i][j]);
        }
    }
    printf("%.1lf", sum_diagonal(matrix, lines, columns));
    lib_matrix(matrix, lines, columns);
    return EXIT_SUCCESS;
}

