#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    double* cgpas = malloc(n * sizeof(double));  // Dynamically allocate array for CGPAs
    if (cgpas == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    // Input CGPAs from user
    for (int i = 0; i < n; i++) {
        printf("Enter CGPA for student %d: ", i + 1);
        //scanf("%lf", &cgpas[i]);
        cgpas[i]=rand()%10;
        printf("%lf \n",cgpas[i]);
    }

    double max_cgpa = 0.0;  // Variable to store the highest CGPA

    // Parallel region to find the maximum CGPA
    #pragma omp parallel for reduction(max:max_cgpa)
    for (int i = 0; i < n; i++) {
        if (cgpas[i] > max_cgpa) {
            max_cgpa = cgpas[i];
        }
    }

    // Output the result
    printf("The highest CGPA is: %.2f\n", max_cgpa);

    // Free allocated memory
    free(cgpas);
    return EXIT_SUCCESS;
}

