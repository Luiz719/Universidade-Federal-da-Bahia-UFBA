#include <stdlib.h>
#include <stdio.h>

double **create_matrix(double lines, double columns){
    double **matrix = (double**)malloc(sizeof(double*) * (int)lines);
    for(int i = 0; i < (int)lines; i++){
        matrix[i] = (double*)malloc(sizeof(double) * (int)columns);
    }
    return matrix;
}

void lib_matrix(double **matrix, double lines, double columns){
    for(int i = 0; i < (int)lines; i++){
        free(matrix[i]);
    }
    free(matrix);
}

double sum_matrix(double **p, double lines, double columns){
    double sum = 0;
    for(int i = 0; i < (int)lines; i++){
        for(int j = 0; j < (int)columns; j++){
            sum += p[i][j];
        }
    }
    return sum;
}


int main(){
    double lines, columns;
    scanf("%lf %lf", &lines, &columns);
    double **matrix = create_matrix(lines, columns);
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            scanf("%lf ", &matrix[i][j]);
        }
    }
    printf("%.1lf", sum_matrix(matrix, lines, columns));
    lib_matrix(matrix, lines, columns);
    return EXIT_SUCCESS;
}

