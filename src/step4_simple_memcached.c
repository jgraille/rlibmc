#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libmemcached/memcached.h>

// Simple function to demonstrate libmemcached basics
void demonstrate_memcached() {
    printf("=== Step 4: libmemcached Demo ===\n");
    
    // 1. Create a memcached instance
    memcached_st *memc = memcached_create(NULL);
    if (!memc) {
        printf("ERROR: Failed to create memcached instance\n");
        return;
    }
    printf("✓ Created memcached instance\n");
    
    // 2. Add a server (localhost:11211)
    memcached_server_st *servers = NULL;
    memcached_return_t rc;
    
    servers = memcached_server_list_append(servers, "localhost", 11211, &rc);
    if (rc != MEMCACHED_SUCCESS) {
        printf("ERROR: Failed to append server: %s\n", memcached_strerror(memc, rc));
        memcached_free(memc);
        return;
    }
    
    rc = memcached_server_push(memc, servers);
    if (rc != MEMCACHED_SUCCESS) {
        printf("ERROR: Failed to push server: %s\n", memcached_strerror(memc, rc));
        memcached_server_list_free(servers);
        memcached_free(memc);
        return;
    }
    printf("✓ Added server localhost:11211\n");
    
    // 3. Try to set a value
    const char *key = "test_key";
    const char *value = "Hello from C!";
    
    rc = memcached_set(memc, key, strlen(key), value, strlen(value), 0, 0);
    if (rc == MEMCACHED_SUCCESS) {
        printf("✓ Set key '%s' = '%s'\n", key, value);
    } else {
        printf("⚠ Failed to set key (memcached might not be running): %s\n", 
               memcached_strerror(memc, rc));
    }
    
    // 4. Try to get the value back
    size_t value_length;
    uint32_t flags;
    char *retrieved_value = memcached_get(memc, key, strlen(key), &value_length, &flags, &rc);
    
    if (rc == MEMCACHED_SUCCESS && retrieved_value) {
        printf("✓ Retrieved key '%s' = '%.*s'\n", key, (int)value_length, retrieved_value);
        free(retrieved_value);  // Important: free the returned value
    } else {
        printf("⚠ Failed to get key: %s\n", memcached_strerror(memc, rc));
    }
    
    // 5. Clean up
    memcached_server_list_free(servers);
    memcached_free(memc);
    printf("✓ Cleaned up resources\n");
    
    printf("=== Demo completed ===\n");
} 