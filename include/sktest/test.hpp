#ifndef sktest_test_hpp
#define sktest_test_hpp

#include <stddef.h>
#include <stdlib.h>

#include <sktest/registration.hpp>
#include <sktest/test_group.hpp>
#include <sktest/assertion.hpp>

// Let SkTest provide the main function.
#ifdef USE_SKTEST_DEFAULT_MAIN_FUNCTION
int main(int _argc, char **_argv) {
  return sktest::RegistrationCenter::get_mutable().invoke_tests();
}
#endif

#endif /* _sktest_test_hpp */