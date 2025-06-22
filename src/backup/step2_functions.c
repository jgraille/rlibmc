#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "step2_functions.h"  // Include our header

// Function implementations
int add_numbers(int a, int b) {
    return a + b;
}

void print_message(const char* message) {
    printf("Message: %s\n", message);
}

char* create_greeting(const char* name) {
    // Allocate memory for the greeting
    char* greeting = (char*)malloc(100 * sizeof(char));
    
    // Create the greeting string
    sprintf(greeting, "Hello, %s! Welcome to C programming.", name);
    
    return greeting;  // Caller must free this memory!
} 