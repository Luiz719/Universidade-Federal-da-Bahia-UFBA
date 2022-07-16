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

double mean_matrix(double **p, int lines, int columns){
    double sum = 0;
    double mean = 0;
    for(int k = 0; k < lines; k++){
        for(int j = 0; j < columns; j++){
            sum += p[k][j];
        }
    }
    mean = sum / (lines * columns);
    return mean;
}


int main(){
    int n, lines, columns;
    scanf("%d\n", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d\n", &lines, &columns);
        double **matrix = create_matrix(lines, columns);
        for(int k = 0; k < lines; k++){
            for(int j = 0; j < columns; j++){
                scanf("%lf ", &matrix[k][j]);
            }
        }
        printf("%.2lf\n", mean_matrix(matrix, lines, columns));
        lib_matrix(matrix, lines, columns);
    }
    return EXIT_SUCCESS;
}

