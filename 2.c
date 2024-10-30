#include <stdio.h>
#include <omp.h>

#define SECTIONS 4

int main() {
    double bills[SECTIONS];  // Array to hold bills for each section
    double total = 0.0;      // Variable to hold the final total

    // Input the bills for each section
    printf("Enter the bill for clothing: ");
    scanf("%lf", &bills[0]);
    printf("Enter the bill for gaming: ");
    scanf("%lf", &bills[1]);
    printf("Enter the bill for grocery: ");
    scanf("%lf", &bills[2]);
    printf("Enter the bill for stationery: ");
    scanf("%lf", &bills[3]);

    // Parallel computation of the total bill
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < SECTIONS; i++) {
        total += bills[i];  // Each thread adds its section's bill to total
    }

    // Display the final total bill
    printf("The total bill amount is: %.2f\n", total);

    return 0;
}

