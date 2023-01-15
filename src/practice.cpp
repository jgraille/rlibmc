#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
bool allC(LogicalVector x) {
    int n = x.size();
    int i = 0;
    while (i < n) {
        if (x[i] == false)return false;
        i++;
    }
    return true;
}
// [[Rcpp::export]]
NumericVector cumprodC(NumericVector x) {
    int n = x.size();
    NumericVector out(n);
    out[0] = x[0];
    int i = 1;
    while (i < n){
        out[i] = out[i - 1] * x[i];
        i++;
    }
    return out;
}

// [[Rcpp::export]]
NumericVector attribs() {
    NumericVector out = NumericVector::create(1, 2, 3);
    out.names() = CharacterVector::create("a", "b", "c");
    out.attr("my-attr") = "my-value";
    //out.attr("class") = "my-class";
    return out;
}
