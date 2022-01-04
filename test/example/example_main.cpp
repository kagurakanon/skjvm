// Let SkTest provide main():
#define USE_SKTEST_DEFAULT_MAIN_FUNCTION
#include <sktest/test.hpp>

#include <stdio.h>

TEST_CASE("hello_world_main") {
    printf("Hello, world!\n");
}