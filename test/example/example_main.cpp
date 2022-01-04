// Let SkTest provide main():
#define USE_SKTEST_DEFAULT_MAIN_FUNCTION
#include <sktest/test.hpp>

test_group ("test operator '+' for integer type") {
  require(1 + 1 != 2, "1 + 1 does not equal 2");
  require(2 + 2 != 4, "2 + 2 does not equal 4");
}