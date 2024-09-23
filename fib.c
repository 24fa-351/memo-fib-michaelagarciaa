#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  
#include <limits.h>  

uint64_t fib_r(int n);  
uint64_t fib_i(int n); 
uint64_t (*fib_func)(int n);

int main(int argc, char *argv[]) {
    int input_number = 0;
    char method = 'r';  
    char *filename = "input.txt";  

    if (argc >= 4) {
        input_number = atoi(argv[1]);
        method = argv[2][0];
        filename = argv[3];
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file '%s'.\n", filename);
        return 1;
    }

    int file_number;
    fscanf(file, "%d", &file_number);
    fclose(file);

    int n = input_number + file_number;

    if (method == 'r') {
        fib_func = fib_r;
    } else if (method == 'i') {
        fib_func = fib_i;
    } else {
        printf("Error: Unknown method '%c'.\n", method);
        return 1;
    }

    uint64_t fibonacci_result = fib_func(n);

    if (fibonacci_result == UINT64_MAX) {
        printf("The Fibonacci number is too large to calculate with 'uint64_t'.\n");
    } else {
        printf("The %dth Fibonacci number is: %llu\n", n, fibonacci_result);
    }

    return 0;
}

uint64_t fib_r(int n) {
    if (n <= 1) {
        return n;
    }
    return fib_r(n - 1) + fib_r(n - 2);
}

uint64_t fib_i(int n) {
    if (n <= 1) {
        return n;
    }

    uint64_t first = 0, second = 1, next_number;
    for (int index = 2; index <= n; index++) {
        if (UINT64_MAX - second < first) {
            return UINT64_MAX;  
        }
        next_number = first + second;
        first = second;
        second = next_number;
    }

    return second;
}
