#include <Rcpp.h>
#include <libmemcached/memcached.h>
#include <string>
#include <vector>

using namespace Rcpp;

// Class to manage memcached connections
class MemcachedClient {
private:
    memcached_st *memc;
    memcached_server_st *servers;
    
public:
    MemcachedClient() {
        memc = memcached_create(NULL);
        servers = NULL;
    }
    
    ~MemcachedClient() {
        if (servers) {
            memcached_server_list_free(servers);
        }
        if (memc) {
            memcached_free(memc);
        }
    }
    
    bool addServer(const std::string& host, int port) {
        memcached_return rc;
        servers = memcached_server_list_append(servers, host.c_str(), port, &rc);
        if (rc != MEMCACHED_SUCCESS) {
            return false;
        }
        
        rc = memcached_server_push(memc, servers);
        return (rc == MEMCACHED_SUCCESS);
    }
    
    bool set(const std::string& key, const std::string& value, time_t expiration = 0) {
        memcached_return rc = memcached_set(memc, 
                                           key.c_str(), key.length(),
                                           value.c_str(), value.length(),
                                           expiration, (uint32_t)0);
        return (rc == MEMCACHED_SUCCESS);
    }
    
    std::string get(const std::string& key) {
        size_t value_length;
        uint32_t flags;
        memcached_return rc;
        
        char *value = memcached_get(memc, 
                                   key.c_str(), key.length(),
                                   &value_length, &flags, &rc);
        
        if (rc == MEMCACHED_SUCCESS && value) {
            std::string result(value, value_length);
            free(value);
            return result;
        }
        
        return "";
    }
    
    bool remove(const std::string& key) {
        memcached_return rc = memcached_delete(memc, key.c_str(), key.length(), 0);
        return (rc == MEMCACHED_SUCCESS);
    }
    
    bool flush(time_t expiration = 0) {
        memcached_return rc = memcached_flush(memc, expiration);
        return (rc == MEMCACHED_SUCCESS);
    }
    
    std::string getLastError() {
        memcached_return rc = memcached_last_error(memc);
        return std::string(memcached_strerror(memc, rc));
    }
};

// Rcpp module to expose the class to R
RCPP_MODULE(MemcachedModule) {
    class_<MemcachedClient>("MemcachedClient")
        .constructor()
        .method("addServer", &MemcachedClient::addServer, "Add a memcached server")
        .method("set", &MemcachedClient::set, "Set a key-value pair")
        .method("get", &MemcachedClient::get, "Get value for a key")
        .method("remove", &MemcachedClient::remove, "Remove a key")
        .method("flush", &MemcachedClient::flush, "Flush all keys")
        .method("getLastError", &MemcachedClient::getLastError, "Get last error message")
    ;
}

// Standalone functions for direct use
// [[Rcpp::export]]
List memcached_connect(std::string host = "localhost", int port = 11211) {
    memcached_st *memc = memcached_create(NULL);
    memcached_server_st *servers = NULL;
    memcached_return rc;
    
    servers = memcached_server_list_append(servers, host.c_str(), port, &rc);
    if (rc != MEMCACHED_SUCCESS) {
        return List::create(Named("success") = false,
                          Named("error") = "Failed to append server");
    }
    
    rc = memcached_server_push(memc, servers);
    memcached_server_list_free(servers);
    
    if (rc == MEMCACHED_SUCCESS) {
        // Store pointer as external pointer
        XPtr<memcached_st> ptr(memc, true);
        return List::create(Named("success") = true,
                          Named("connection") = ptr);
    } else {
        memcached_free(memc);
        return List::create(Named("success") = false,
                          Named("error") = memcached_strerror(memc, rc));
    }
}

// [[Rcpp::export]]
bool memcached_set_value(SEXP conn, std::string key, std::string value, int expiration = 0) {
    XPtr<memcached_st> memc(conn);
    if (!memc) {
        stop("Invalid connection object");
    }
    
    memcached_return rc = memcached_set(memc, 
                                       key.c_str(), key.length(),
                                       value.c_str(), value.length(),
                                       (time_t)expiration, (uint32_t)0);
    return (rc == MEMCACHED_SUCCESS);
}

// [[Rcpp::export]]
std::string memcached_get_value(SEXP conn, std::string key) {
    XPtr<memcached_st> memc(conn);
    if (!memc) {
        stop("Invalid connection object");
    }
    
    size_t value_length;
    uint32_t flags;
    memcached_return rc;
    
    char *value = memcached_get(memc, 
                               key.c_str(), key.length(),
                               &value_length, &flags, &rc);
    
    if (rc == MEMCACHED_SUCCESS && value) {
        std::string result(value, value_length);
        free(value);
        return result;
    }
    
    return "";
}

// [[Rcpp::export]]
bool memcached_delete_key(SEXP conn, std::string key) {
    XPtr<memcached_st> memc(conn);
    if (!memc) {
        stop("Invalid connection object");
    }
    
    memcached_return rc = memcached_delete(memc, key.c_str(), key.length(), 0);
    return (rc == MEMCACHED_SUCCESS);
}

// [[Rcpp::export]]
void memcached_disconnect(SEXP conn) {
    XPtr<memcached_st> memc(conn);
    if (memc) {
        memc.release();  // XPtr will handle cleanup
    }
} 