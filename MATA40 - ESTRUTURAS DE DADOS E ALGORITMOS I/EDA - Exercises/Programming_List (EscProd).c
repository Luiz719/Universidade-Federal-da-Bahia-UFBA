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

double **multi_matrix(double **p, double **q, int lines,
                      int columns, int lines2, int columns2){
    double **r = create_matrix(lines, columns2);
    double temp_sum = 0;
    for(int k = 0; k < lines; k++){
        for(int j = 0; j < columns2; j++){
            for(int i = 0; i < columns; i++){
                temp_sum += p[k][i] * q[i][j];
            }
            r[k][j] = temp_sum;
            temp_sum = 0;
        }
    }
    return r;
}


int main(){
    int n, lines, columns, lines2, columns2;
    scanf("%d\n", &n);
    scanf("%d %d\n", &lines, &columns);
    double **matrix = create_matrix(lines, columns);
    for(int k = 0; k < lines; k++){
        for(int j = 0; j < columns; j++){
            scanf("%lf ", &matrix[k][j]);
        }
    }
    for(int i = 0; i < n - 1; i++){
        scanf("%d %d\n", &lines2, &columns2);
        double **matrix2 = create_matrix(lines2, columns2);
        for(int k = 0; k < lines2; k++){
            for(int j = 0; j < columns2; j++){
                scanf("%lf ", &matrix2[k][j]);
            }
        }
        matrix = multi_matrix(matrix, matrix2, lines, columns, lines2, columns2);
        lib_matrix(matrix2, lines2, columns2);
        columns = columns2;
    }
    print_matrix(matrix, lines, columns);
    lib_matrix(matrix, lines, columns);
    return EXIT_SUCCESS;
}

