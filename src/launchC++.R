rm(list = ls())
library(Rcpp)
library(here)
sourceCpp(here("src/practice.cpp"))

allC(c(TRUE,TRUE))
allC(c(TRUE, FALSE))
allC(c(FALSE,FALSE))

quit(save = 'no')