#' R Client for Memcached
#' 
#' @description
#' This package provides an R interface to memcached using libmemcached.
#' 
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @useDynLib rlibmc, .registration = TRUE
#' @exportPattern "^[[:alpha:]]+"
NULL

#' Create a new Memcached connection
#' 
#' @param host Character string specifying the memcached server host
#' @param port Integer specifying the memcached server port
#' @return A memcached connection object
#' @export
#' @examples
#' \dontrun{
#' mc <- mc_connect("localhost", 11211)
#' }
mc_connect <- function(host = "localhost", port = 11211L) {
  result <- memcached_connect(host, as.integer(port))
  if (!result$success) {
    stop("Failed to connect to memcached: ", result$error)
  }
  
  # Create an S3 object with the connection
  structure(
    list(connection = result$connection, 
         host = host, 
         port = port),
    class = "memcached_connection"
  )
}

#' Set a value in memcached
#' 
#' @param conn A memcached connection object from mc_connect()
#' @param key Character string key
#' @param value Character string value
#' @param expiration Integer expiration time in seconds (0 = no expiration)
#' @return Logical indicating success
#' @export
#' @examples
#' \dontrun{
#' mc <- mc_connect()
#' mc_set(mc, "mykey", "myvalue")
#' mc_set(mc, "tempkey", "tempvalue", expiration = 60)
#' }
mc_set <- function(conn, key, value, expiration = 0L) {
  if (!inherits(conn, "memcached_connection")) {
    stop("conn must be a memcached_connection object")
  }
  
  # Convert R objects to strings if needed
  if (!is.character(value)) {
    value <- as.character(value)
  }
  
  memcached_set_value(conn$connection, 
                      as.character(key), 
                      value, 
                      as.integer(expiration))
}

#' Get a value from memcached
#' 
#' @param conn A memcached connection object from mc_connect()
#' @param key Character string key
#' @return The value associated with the key, or NA if not found
#' @export
#' @examples
#' \dontrun{
#' mc <- mc_connect()
#' mc_set(mc, "mykey", "myvalue")
#' value <- mc_get(mc, "mykey")
#' }
mc_get <- function(conn, key) {
  if (!inherits(conn, "memcached_connection")) {
    stop("conn must be a memcached_connection object")
  }
  
  value <- memcached_get_value(conn$connection, as.character(key))
  if (value == "") {
    return(NA_character_)
  }
  value
}

#' Delete a key from memcached
#' 
#' @param conn A memcached connection object from mc_connect()
#' @param key Character string key
#' @return Logical indicating success
#' @export
#' @examples
#' \dontrun{
#' mc <- mc_connect()
#' mc_set(mc, "mykey", "myvalue")
#' mc_delete(mc, "mykey")
#' }
mc_delete <- function(conn, key) {
  if (!inherits(conn, "memcached_connection")) {
    stop("conn must be a memcached_connection object")
  }
  
  memcached_delete_key(conn$connection, as.character(key))
}

#' Disconnect from memcached
#' 
#' @param conn A memcached connection object from mc_connect()
#' @return NULL
#' @export
#' @examples
#' \dontrun{
#' mc <- mc_connect()
#' mc_disconnect(mc)
#' }
mc_disconnect <- function(conn) {
  if (!inherits(conn, "memcached_connection")) {
    stop("conn must be a memcached_connection object")
  }
  
  memcached_disconnect(conn$connection)
  invisible(NULL)
}

#' Print method for memcached connections
#' 
#' @param x A memcached connection object
#' @param ... Additional arguments (ignored)
#' @return The object invisibly
#' @export
print.memcached_connection <- function(x, ...) {
  cat("Memcached connection\n")
  cat("  Host:", x$host, "\n")
  cat("  Port:", x$port, "\n")
  invisible(x)
}

#' Create a Memcached Client using R6 interface
#' 
#' @description
#' Alternative object-oriented interface using Rcpp modules
#' 
#' @export
#' @examples
#' \dontrun{
#' client <- MemcachedClient$new()
#' client$addServer("localhost", 11211)
#' client$set("key", "value")
#' value <- client$get("key")
#' }
MemcachedClient <- function() {
  Rcpp::Module("MemcachedModule", PACKAGE = "rlibmc")$MemcachedClient
} 