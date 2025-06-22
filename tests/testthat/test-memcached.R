test_that("memcached connection works", {
  skip_if_not(pingr::is_up("localhost", 11211), "Memcached server not available")
  
  mc <- mc_connect("localhost", 11211)
  expect_s3_class(mc, "memcached_connection")
  expect_equal(mc$host, "localhost")
  expect_equal(mc$port, 11211)
  
  mc_disconnect(mc)
})

test_that("basic set and get operations work", {
  skip_if_not(pingr::is_up("localhost", 11211), "Memcached server not available")
  
  mc <- mc_connect()
  
  # Test setting and getting a value
  result <- mc_set(mc, "test_key", "test_value")
  expect_true(result)
  
  value <- mc_get(mc, "test_key")
  expect_equal(value, "test_value")
  
  # Test non-existent key
  missing <- mc_get(mc, "non_existent_key")
  expect_true(is.na(missing))
  
  mc_disconnect(mc)
})

test_that("delete operation works", {
  skip_if_not(pingr::is_up("localhost", 11211), "Memcached server not available")
  
  mc <- mc_connect()
  
  # Set a value
  mc_set(mc, "delete_test", "value")
  expect_equal(mc_get(mc, "delete_test"), "value")
  
  # Delete it
  result <- mc_delete(mc, "delete_test")
  expect_true(result)
  
  # Verify it's gone
  expect_true(is.na(mc_get(mc, "delete_test")))
  
  mc_disconnect(mc)
})

test_that("expiration works", {
  skip_if_not(pingr::is_up("localhost", 11211), "Memcached server not available")
  
  mc <- mc_connect()
  
  # Set a value with 1 second expiration
  mc_set(mc, "expire_test", "temporary", expiration = 1)
  
  # Should exist immediately
  expect_equal(mc_get(mc, "expire_test"), "temporary")
  
  # Wait and check if expired
  Sys.sleep(2)
  expect_true(is.na(mc_get(mc, "expire_test")))
  
  mc_disconnect(mc)
})

test_that("numeric values are converted to strings", {
  skip_if_not(pingr::is_up("localhost", 11211), "Memcached server not available")
  
  mc <- mc_connect()
  
  mc_set(mc, "number", 42)
  expect_equal(mc_get(mc, "number"), "42")
  
  mc_set(mc, "float", 3.14)
  expect_equal(mc_get(mc, "float"), "3.14")
  
  mc_disconnect(mc)
}) 