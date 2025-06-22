rm(list = ls())
library(Rcpp)
library(here)
sourceCpp(here("src/arkiv/practice.cpp"))

allC(c(TRUE,TRUE))
allC(c(TRUE, FALSE))
allC(c(FALSE,FALSE))

cumprodC(c(1,2,3,4))

quit(save = 'no')
