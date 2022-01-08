#include <sktest/test.hpp>
#include <string.h>

test_group ("test string comparison (strcmp)") {
  assert_true(strcmp("a", "a") == 0);
  assert_true(strcmp("a", "b") < 0);
  assert_true(strcmp("b", "a") > 0);

  assert_equal(strcmp("a", "b"), 0, "\"a\" and \"b\" are not the same");
}

test_group ("test string length (strlen)") {
  assert_equal(strlen("a"), 1);
  assert_equal(strlen("ab"), 2);
  assert_equal(strlen("abc"), 3);

  assert_equal(strlen("a"), 0, "string \"a\" should have length 1");
}