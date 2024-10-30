#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void initialize_matrix_vector(int n, double A[n][n], double B[n]) {
    for (int i = 0; i < n; i++) {
        B[i] = rand() % 10;  // Initialize vector B with random values
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;  // Initialize matrix A with random values
        }
    }
}

void parallel_matrix_vector_multiply(int n, double A[n][n], double B[n], double C[n]) {
    #pragma omp parallel for ordered
    for (int i = 0; i < n; i++) {
        C[i] = 0;  // Initialize C[i]
        for (int j = 0; j < n; j++) {
            C[i] += A[i][j] * B[j];
        }

        // Use ordered section to print in a consistent order
        #pragma omp ordered
        printf("C[%d] = %f\n", i, C[i]);
    }
}

int main() {
    int n = 1000;  // Change this for different sizes
    double (*A)[n] = malloc(n * n * sizeof(double));
    double *B = malloc(n * sizeof(double));
    double *C = malloc(n * sizeof(double));

    // Initialize matrix and vector
    srand(time(NULL));
    initialize_matrix_vector(n, A, B);

    // Perform matrix-vector multiplication
    parallel_matrix_vector_multiply(n, A, B, C);

    // Free allocated memory
    free(A);
    free(B);
    free(C);

    return 0;
}

