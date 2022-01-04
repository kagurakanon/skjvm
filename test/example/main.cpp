#define USE_SKTEST_DEFAULT_MAIN_FUNCTION
#include <sktest/test.hpp>

test_group ("test SkTest itself") {
  require(true, "this assertion should pass");
  require(false, "this assertion should fail");
}
