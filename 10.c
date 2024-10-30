#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 500  // Change this to 2000 or 3000 for larger matrices

void initialize_matrices(int n, double matrix1[n][n], double matrix2[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix1[i][j] = rand() % 10;  // Initialize with random values
            matrix2[i][j] = rand() % 10;  // Initialize with random values
        }
    }
}

void sequential_matrix_multiply(int n, double matrix1[n][n], double matrix2[n][n], double result[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void parallel_matrix_multiply(int n, double matrix1[n][n], double matrix2[n][n], double result[n][n]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main() {
    double (*matrix1)[SIZE] = malloc(SIZE * SIZE * sizeof(double));
    double (*matrix2)[SIZE] = malloc(SIZE * SIZE * sizeof(double));
    double (*result_sequential)[SIZE] = malloc(SIZE * SIZE * sizeof(double));
    double (*result_parallel)[SIZE] = malloc(SIZE * SIZE * sizeof(double));

    // Initialize matrices
    srand(time(NULL));
    initialize_matrices(SIZE, matrix1, matrix2);

    // Measure sequential multiplication
    double start_time = omp_get_wtime();
    sequential_matrix_multiply(SIZE, matrix1, matrix2, result_sequential);
    double end_time = omp_get_wtime();
    printf("Sequential Time: %f seconds\n", end_time - start_time);

    // Measure parallel multiplication
    start_time = omp_get_wtime();
    parallel_matrix_multiply(SIZE, matrix1, matrix2, result_parallel);
    end_time = omp_get_wtime();
    printf("Parallel Time: %f seconds\n", end_time - start_time);

    // Free allocated memory
    free(matrix1);
    free(matrix2);
    free(result_sequential);
    free(result_parallel);
    

    return 0;
}

