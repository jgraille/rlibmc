bacic2 <- function(n) {
.C("basic", as.integer(n))
}