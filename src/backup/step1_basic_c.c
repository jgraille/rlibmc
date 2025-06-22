#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Basic C program to demonstrate fundamentals
int main() {
    // Variables and basic types
    int number = 42;
    char text[100] = "Hello, World!";
    char *dynamic_text;
    
    // Print basic info
    printf("Number: %d\n", number);
    printf("Text: %s\n", text);
    
    // Dynamic memory allocation
    dynamic_text = (char*)malloc(50 * sizeof(char));
    strcpy(dynamic_text, "Dynamic string");
    printf("Dynamic: %s\n", dynamic_text);
    
    // Always free allocated memory
    free(dynamic_text);
    
    return 0;
} 