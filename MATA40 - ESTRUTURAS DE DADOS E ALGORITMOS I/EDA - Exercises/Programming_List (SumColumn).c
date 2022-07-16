#include <stdlib.h>
#include <stdio.h>

double **create_matrix(int lines, int columns){
    double **matrix = (double**)malloc(sizeof(double*) * lines);
    for(int i = 0; i < lines; i++){
        matrix[i] = (double*)malloc(sizeof(double) * columns);
    }
    return matrix;
}

void print_matrix(double **matrix, int lines, int columns){
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            printf("%.1lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void lib_matrix(double **matrix, int lines, int columns){
    for(int i = 0; i < lines; i++){
        free(matrix[i]);
    }
    free(matrix);
}

double sum_column(double **p, int lines, int columns){
    double sum = 0;
    for(int j = 0; j < lines; j++){
        sum += p[j][0];
    }
    return sum;
}


int main(){
    int lines, columns;
    scanf("%d %d", &lines, &columns);
    double **matrix = create_matrix(lines, columns);
    double **matrix_trans = create_matrix(columns, lines);
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            scanf("%lf ", &matrix[i][j]);
        }
    }
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            matrix_trans[j][i] = matrix[i][j];
        }
    }
    print_matrix(matrix_trans, columns, lines);
    printf("%.1lf", sum_column(matrix_trans, columns, lines));
    lib_matrix(matrix, lines, columns);
    lib_matrix(matrix_trans, columns, lines);
    return EXIT_SUCCESS;
}

