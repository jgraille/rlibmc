# http://adv-r.had.co.nz/Rcpp.html

rm(list = ls())
library(Rcpp)

#one <- function() 1L

cppFunction("int one() {
    return 1;    
}")


cppFunction('int signC(int x) {
  if (x > 0) {
    return 1;
  } else if (x == 0) {
    return 0;
  } else {
    return -1;
  }
}')

signC(1)
signC(0)
signC(-1)

cppFunction('double sumC(NumericVector x) {
    int n = x.size();
    double total = 0;
    for(int i=0; i<n; ++i) {
        total +=x[i];
    }
    return total;
}')

sumC(c(1,2,4,4))
