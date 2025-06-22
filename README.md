# rlibmc

An R client for memcached key-value store using libmemcached.

## Installation

### Prerequisites

**On macOS**:
```bash
brew install libmemcached
```

**On Ubuntu/Debian**:
```bash
sudo apt-get install libmemcached-dev
```

**On CentOS/RHEL**:
```bash
sudo yum install libmemcached-devel
```

### Install the R package

```r
# Install from source
devtools::install_github("yourusername/rlibmc")

# Or build and install locally
devtools::install()
```

## Usage

### Basic Usage

```r
library(rlibmc)

# Connect to memcached
mc <- mc_connect("localhost", 11211)

# Set values
mc_set(mc, "name", "John Doe")
mc_set(mc, "age", "30")
mc_set(mc, "temp", "expires soon", expiration = 60)  # expires in 60 seconds

# Get values
name <- mc_get(mc, "name")  # "John Doe"
age <- mc_get(mc, "age")    # "30"

# Delete a key
mc_delete(mc, "age")

# Disconnect
mc_disconnect(mc)
```

### Object-Oriented Interface

```r
# Create client using Rcpp modules
client <- MemcachedClient()$new()

# Add server
client$addServer("localhost", 11211)

# Operations
client$set("key", "value")
value <- client$get("key")
client$remove("key")
```

### Storing R Objects

```r
# Serialize R objects for storage
data <- list(x = 1:10, y = rnorm(10))
mc <- mc_connect()

# Store serialized object
serialized <- rawToChar(serialize(data, NULL, ascii = TRUE))
mc_set(mc, "r_data", serialized)

# Retrieve and deserialize
retrieved <- mc_get(mc, "r_data")
data_back <- unserialize(charToRaw(retrieved))

mc_disconnect(mc)
```

## API Reference

### Connection Functions

- `mc_connect(host = "localhost", port = 11211)` - Create connection
- `mc_disconnect(conn)` - Close connection

### Data Operations

- `mc_set(conn, key, value, expiration = 0)` - Store key-value pair
- `mc_get(conn, key)` - Retrieve value (returns NA if not found)
- `mc_delete(conn, key)` - Delete a key

### Object-Oriented API

- `MemcachedClient()$new()` - Create new client instance
- `client$addServer(host, port)` - Add server
- `client$set(key, value, expiration)` - Store value
- `client$get(key)` - Retrieve value
- `client$remove(key)` - Delete key
- `client$flush(expiration)` - Flush all keys
- `client$getLastError()` - Get last error message

## Development Status

- ✅ Basic connection management
- ✅ Get/Set/Delete operations
- ✅ Expiration support
- ✅ Both functional and OO interfaces
- ✅ Rcpp integration
- 🔲 Binary data support
- 🔲 Multi-get operations
- 🔲 CAS (Compare-And-Swap) operations
- 🔲 Connection pooling

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

MPL-2.0

## References

- [libmemcached documentation](http://libmemcached.org/)
- [Rcpp documentation](http://www.rcpp.org/)
- [Writing R Extensions](https://cran.r-project.org/doc/manuals/r-release/R-exts.html)

# features status
- Step one [Done] -> practising with this doc http://adv-r.had.co.nz/C-interface.html
- Step two [On going] -> practising with Rcpp [Done]
- Step third -> Understanding of the _pylibmcmodule.c/_pylibmcmodule.h

# Annexes
http://colinfay.me/r-internals/r-internal-structures.html
https://www.biostat.jhsph.edu/~rpeng/docs/interface.pdf
https://docs.oracle.com/cd/E17952_01/mysql-5.6-en/ha-memcached-interfaces-libmemcached.html