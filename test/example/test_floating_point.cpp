#include <sktest/test.hpp>

test_group ("test addition operator for float (`+`)") {
  require(1.0 + 1.0 == 2.0);
  require(1.0 + 2.0 == 3.0);
}

test_group ("test subtraction operator for float (`-`)") {
  require(2.0 - 1.0 == 1.0);
  require(3.0 - 2.0 == 1.0);
  require(4.0 - 3.0 == 1.0);
}
