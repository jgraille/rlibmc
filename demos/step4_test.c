#include <stdio.h>

// Declare our function (it's in step4_simple_memcached.c)
void demonstrate_memcached();

int main() {
    printf("Testing libmemcached integration...\n\n");
    
    demonstrate_memcached();
    
    printf("\nNote: If you see warnings above, make sure memcached is running:\n");
    printf("  brew install memcached\n");
    printf("  memcached -p 11211 -d\n");
    
    return 0;
} 