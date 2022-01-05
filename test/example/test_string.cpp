#include <sktest/test.hpp>
#include <string.h>

test_group ("test string comparison (strcmp)") {
  require(strcmp("a", "a") == 0);
  require(strcmp("a", "b") < 0);
  require(strcmp("b", "a") > 0);

  require(strcmp("a", "b") == 0);
}

test_group ("test string length (strlen)") {
  require(strlen("a") == 1);
  require(strlen("ab") == 2);
  require(strlen("abc") == 3);

  require(strlen("a") == 0, "string \"a\" should have length 1");
}