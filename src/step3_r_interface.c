#include <R.h>          // R headers
#include <Rinternals.h> // R internal functions

// Simple C function that R can call
// This uses R's .C() interface
void hello_from_c(int *n) {
    int i;
    
    // Rprintf is like printf but for R
    Rprintf("=== Hello from C! ===\n");
    
    for (i = 0; i < *n; i++) {
        Rprintf("Message %d: C is working with R!\n", i + 1);
    }
    
    Rprintf("=== End of C function ===\n");
}

// More advanced function using SEXP (R objects)
// This uses R's .Call() interface
SEXP add_vectors(SEXP x, SEXP y) {
    // Get the length of the vectors
    int n = length(x);
    
    // Create a new R vector to return
    SEXP result = PROTECT(allocVector(REALSXP, n));
    
    // Get pointers to the data
    double *px = REAL(x);
    double *py = REAL(y);
    double *presult = REAL(result);
    
    // Add the vectors element by element
    for (int i = 0; i < n; i++) {
        presult[i] = px[i] + py[i];
    }
    
    // Unprotect and return
    UNPROTECT(1);
    return result;
} 