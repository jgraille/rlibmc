rm(list = ls())
library(Rcpp)
# no inputs, scalar output
cppFunction("int one() {
  return 1;
}")
one()

# scala input,scalar output
cppFunction('int signC(int x) {
  if (x > 0) {
    return 1;
  } else {
    return 0;
  }
}')

# vector input,scalar input
sumR <- function(x) {
  total <- 0
  for (i in seq_along(x)) {
    total <- total + x[i]
  }
  total
}
cppFunction("double sumC(NumericVector x) {
  int n = x.size();
  double total = 0;
  for(int i = 0; i < n; ++i) {
    total += x[i];
  }
  return total;
}")
x <- runif(1e3)
microbenchmark(
  sum(x),
  sumC(x),
  sumR(x)
)
