#include <stdio.h>
#include <stdlib.h>
#include "step2_functions.h"  // Include our header

int main() {
    printf("=== Step 2: C Functions Demo ===\n");
    
    // Use our functions
    int result = add_numbers(10, 20);
    printf("10 + 20 = %d\n", result);
    
    print_message("This is a test message");
    
    // Use function that returns allocated memory
    char* greeting = create_greeting("John");
    printf("%s\n", greeting);
    
    // IMPORTANT: Free the allocated memory
    free(greeting);
    
    printf("=== Demo completed successfully! ===\n");
    return 0;
} 