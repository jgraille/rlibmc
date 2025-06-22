# Basic usage example for rlibmc
# Make sure memcached is running on localhost:11211

library(rlibmc)

# Method 1: Functional interface
# ------------------------------

# Connect to memcached
mc <- mc_connect("localhost", 11211)
print(mc)

# Set some values
mc_set(mc, "name", "John Doe")
mc_set(mc, "age", "30")
mc_set(mc, "temp_data", "This will expire", expiration = 60)  # expires in 60 seconds

# Get values
name <- mc_get(mc, "name")
age <- mc_get(mc, "age")
cat("Name:", name, "\n")
cat("Age:", age, "\n")

# Try to get non-existent key
missing <- mc_get(mc, "nonexistent")
cat("Missing value:", missing, "\n")  # Should be NA

# Delete a key
mc_delete(mc, "age")
age_after_delete <- mc_get(mc, "age")
cat("Age after delete:", age_after_delete, "\n")  # Should be NA

# Disconnect
mc_disconnect(mc)


# Method 2: Object-oriented interface (using Rcpp modules)
# -------------------------------------------------------

# Create client instance
client <- MemcachedClient()$new()

# Add server
success <- client$addServer("localhost", 11211)
if (success) {
  cat("Successfully connected to memcached server\n")
} else {
  cat("Failed to connect:", client$getLastError(), "\n")
}

# Set and get values
client$set("user:1", "Alice")
client$set("user:2", "Bob")

user1 <- client$get("user:1")
user2 <- client$get("user:2")
cat("User 1:", user1, "\n")
cat("User 2:", user2, "\n")

# Remove a key
client$remove("user:1")

# Flush all keys (use with caution!)
# client$flush()


# Working with R objects
# ---------------------

# You can store serialized R objects by converting them to strings
data <- list(x = 1:10, y = rnorm(10))
mc <- mc_connect()

# Serialize and store
serialized <- rawToChar(serialize(data, NULL, ascii = TRUE))
mc_set(mc, "r_object", serialized)

# Retrieve and deserialize
retrieved <- mc_get(mc, "r_object")
if (!is.na(retrieved)) {
  data_back <- unserialize(charToRaw(retrieved))
  print(data_back)
}

mc_disconnect(mc) 