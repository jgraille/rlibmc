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
