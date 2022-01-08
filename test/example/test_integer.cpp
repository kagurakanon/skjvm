#include <sktest/test.hpp>

test_group ("test addition operator for integer (`+`)") {
  assert_true(1 + 1 == 2);
  assert_true(1 + 1 == 3);
  assert_true(2 + 3 == 4, "2 + 3 should not equal 4");

  assert_false(1 + 1 == 3);
  assert_false(2 + 2 == 3);
  assert_false(3 + 3 == 4);
}

test_group ("test subtraction operator for integer (`-`)") {
  assert_equal(2 - 1, 1);
  assert_equal(3 - 2, 4, "3 - 2 should not equal 4");
  assert_not_equal(4 - 2, 2);
}