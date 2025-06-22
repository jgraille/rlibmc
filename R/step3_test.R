# R functions to test our C code

# Test the simple .C() interface
test_hello_c <- function(n = 3) {
  cat("Calling C function from R...\n")
  .C("hello_from_c", as.integer(n))
  cat("Back in R!\n")
}

# Test the .Call() interface  
test_add_vectors <- function() {
  cat("Testing vector addition in C...\n")
  
  x <- c(1.0, 2.0, 3.0, 4.0)
  y <- c(10.0, 20.0, 30.0, 40.0)
  
  cat("x =", x, "\n")
  cat("y =", y, "\n")
  
  result <- .Call("add_vectors", x, y)
  cat("x + y =", result, "\n")
  
  return(result)
} 