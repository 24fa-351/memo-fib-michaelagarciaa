#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  
#include <limits.h>  

uint64_t fib_r(int n); 
uint64_t fib_i(int n);  
uint64_t (*fib_func)(int n);

uint64_t *memo_r = NULL;  
uint64_t *memo_i = NULL; 

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

    memo_r = (uint64_t *)malloc((n + 1) * sizeof(uint64_t));
    memo_i = (uint64_t *)malloc((n + 1) * sizeof(uint64_t));

    if (memo_r == NULL || memo_i == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i <= n; i++) {
        memo_r[i] = UINT64_MAX;
        memo_i[i] = UINT64_MAX;
    }

    if (method == 'r') {
        fib_func = fib_r;
    } else if (method == 'i') {
        fib_func = fib_i;
    } else {
        printf("Error: Unknown method '%c'.\n", method);
        free(memo_r);
        free(memo_i);
        return 1;
    }

    uint64_t fibonacci_result = fib_func(n);

    if (fibonacci_result == UINT64_MAX) {
        printf("The Fibonacci number is too large to calculate with 'uint64_t'.\n");
    } else {
        printf("The %dth Fibonacci number is: %llu\n", n, fibonacci_result);
    }

    free(memo_r);
    free(memo_i);

    return 0;
}

uint64_t fib_r(int n) {
    if (n <= 1) {
        return n;
    }

    if (memo_r[n] != UINT64_MAX) {
        return memo_r[n];
    }

    memo_r[n] = fib_r(n - 1) + fib_r(n - 2);
    return memo_r[n];
}

uint64_t fib_i(int n) {
    if (n <= 1) {
        return n;
    }

    if (memo_i[n] != UINT64_MAX) {
        return memo_i[n];  
    }

    uint64_t first = 0, second = 1, next_number;
    for (int index = 2; index <= n; index++) {
        if (UINT64_MAX - second < first) {
            return UINT64_MAX;  
        }
        next_number = first + second;
        first = second;
        second = next_number;
        memo_i[index] = second;  
    }

    return second;
}
