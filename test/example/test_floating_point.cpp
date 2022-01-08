#include <sktest/test.hpp>

test_group ("test addition operator for float (`+`)") {
  assert_equal(1.0 + 1.0, 2.0); // NOLINT
  assert_equal(1.0 + 2.0, 3.0); // NOLINT
}

test_group ("test subtraction operator for float (`-`)") {
  assert_equal(2.0 - 1.0, 1.0);
  assert_equal(3.0 - 2.0, 1.0);
  assert_equal(4.0 - 3.0, 1.0);
}
