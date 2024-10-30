#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_FIB 1000 // Maximum Fibonacci number (can be changed)

int fib[MAX_FIB];  // Array to store Fibonacci numbers
int count = 0;     // Count of generated Fibonacci numbers

void generate_fibonacci(int max_value) {
    int a = 0, b = 1, next;
    fib[count++] = a;  // F(0)
    
    while (b <= max_value) {
        fib[count++] = b;  // Store Fibonacci number
        next = a + b;      // Calculate next Fibonacci number
        a = b;             // Update for next iteration
        b = next;          // Update for next iteration
    }
}

void print_fibonacci() {
    for (int i = 0; i < count; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");
}

int main() {
    int max_value;

    printf("Enter the maximum value for Fibonacci series: ");
    scanf("%d", &max_value);

    // Start OpenMP parallel region
    #pragma omp parallel
    {
        #pragma omp single
        {
            // Generate Fibonacci numbers
            #pragma omp task
            generate_fibonacci(max_value);
            
            // Print Fibonacci numbers
            #pragma omp task
            print_fibonacci();
        }
    }

    return 0;
}

