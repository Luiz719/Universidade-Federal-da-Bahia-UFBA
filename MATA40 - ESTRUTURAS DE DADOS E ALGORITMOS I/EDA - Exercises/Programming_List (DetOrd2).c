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

double detord2(double **p, int lines, int columns){
    double det = 0;
    det = p[0][0] * p[1][1] - p[0][1] * p[1][0];
    return det;
}

int main(){
    int lines = 2, columns = 2;
    double **matrix = create_matrix(lines, columns);
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            scanf("%lf ", &matrix[i][j]);
        }
    }
    printf("%.1lf", detord2(matrix, lines, columns));
    lib_matrix(matrix, lines, columns);
    return EXIT_SUCCESS;
}

