#include <sktest/test.hpp>

test_group ("test addition operator for integer (`+`)") {
  assert_true(1 + 1 == 2);
  assert_true(1 + 1 == 3);
  assert_true(2 + 2 == 4);
}

//test_group ("test subtraction operator for integer (`-`)") {
//  require(2 - 1 == 1);
//  require(3 - 2 == 1);
//  require(4 - 2 == 1);
//}