#include <sktest/test.hpp>

test_group ("test addition operator for integer (`+`)") {
  require(1 + 1 == 2);
  require(1 + 2 == 3);
  require(2 + 2 == 4);
}

test_group ("test subtraction operator for integer (`-`)") {
  require(2 - 1 == 1);
  require(3 - 2 == 1);
  require(4 - 2 == 1);
}