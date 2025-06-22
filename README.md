# rlibmc

R client for memcached using libmemcached - A step-by-step learning approach.

## Overview

This project demonstrates how to build an R package that interfaces with external C libraries, specifically `libmemcached`. It's designed as a learning journey through C/R integration.

## Prerequisites

**On macOS**:
```bash
brew install libmemcached memcached
```

**On Ubuntu/Debian**:
```bash
sudo apt-get install libmemcached-dev memcached
```

## Quick Start

```bash
# 1. Compile the demo
gcc -I/opt/homebrew/include -L/opt/homebrew/lib -o step4_demo \
    src/step4_simple_memcached.c demos/step4_test.c -lmemcached

# 2. Start memcached server
memcached -p 11211 -d

# 3. Run the demo
./step4_demo
```

Expected output:
```
=== Step 4: libmemcached Demo ===
✓ Created memcached instance
✓ Added server localhost:11211
✓ Set key 'test_key' = 'Hello from C!'
✓ Retrieved key 'test_key' = 'Hello from C!'
✓ Cleaned up resources
=== Demo completed ===
```

## Project Structure

```
rlibmc/
├── src/                          # Library code (functions, no main)
│   ├── step4_simple_memcached.c  # Core libmemcached functionality
│   └── arkiv/                    # Archive of learning exercises
├── demos/                        # Example programs (with main)
│   └── step4_test.c              # Demo program for Step 4
└── R/                            # R interface code (future)
```

## Learning Steps

- ✅ **Step 4**: Basic libmemcached integration in C
- 🔄 **Step 5**: R-C integration (next)
- 📋 **Step 6**: Complete R package

## Common Issues

**Compilation error**: `libmemcached/memcached.h not found`
```bash
brew install libmemcached
```

**Runtime error**: `CONNECTION FAILURE`
```bash
memcached -p 11211 -d
```

## Key Concepts

- **`src/`** folder: Library functions (no `main()`)
- **`demos/`** folder: Executable programs (with `main()`)
- **Memory management**: Always `free()` what you `malloc()`
- **Error handling**: Check return codes, use `memcached_strerror()`

## Next Steps

1. Integrate libmemcached with R using `.C()` interface
2. Build complete R package with documentation
3. Add advanced features (connection pooling, etc.)

## References

- [Advanced R - C Interface](http://adv-r.had.co.nz/C-interface.html)
- [R Internal Structures](http://colinfay.me/r-internals/r-internal-structures.html)
- [R-C Interface Guide](https://www.biostat.jhsph.edu/~rpeng/docs/interface.pdf)
- [libmemcached Documentation](https://docs.oracle.com/cd/E17952_01/mysql-5.6-en/ha-memcached-interfaces-libmemcached.html)