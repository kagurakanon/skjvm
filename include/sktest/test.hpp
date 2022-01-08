/// \brief SkTest is a C++ unit testing framework for project Shinkai JVM.
///
/// \details To use SkTest, you need to include \c \<sktest/test.hpp\> in your
/// test file. SkTest is a header-only library, so linking is not necessary. Do
/// not include other headers like \c \<sktest/assertion.hpp\> and
/// \c \<sktest/test_group.hpp\> directly. Except for macro
/// \c USE_SKTEST_DEFAULT_MAIN_FUNCTION, \c test_group and \c require, all other
/// APIs are private.
///
/// \details Define \c USE_SKTEST_DEFAULT_MAIN_FUNCTION in the top of your test
/// file (before you include the \c \<sktest/test.hpp\>) to let SkTest
/// provide \c main() function automatically. You may include
/// \c \<sktest/test.hpp\> in every \c .cpp test file, but the macro
/// \c USE_SKTEST_DEFAULT_MAIN_FUNCTION should only be defined once. Otherwise
/// you may meet the duplicate main problem.
///
/// \details
/// \code
/// #define USE_SKTEST_DEFAULT_MAIN_FUNCTION
/// #include &lt;sktest/test.hpp>
///
/// test_group ("test operator '+' for integer type") {
///     assert_true(1 + 1 == 2, "1 + 1 does not equal 2");
///     assert_true(2 + 2 == 4, "2 + 2 does not equal 4");
/// }
///
/// test_group ("test operator '-' for integer type") {
///     assert_true(2 - 1 == 1, "2 - 1 does not equal 1");
///     assert_true(4 - 2 == 4, "4 - 2 does not equal 2");
/// }
/// \endcode
///
/// \details You can find richer examples in the \c test/example directory.
///
/// \note SkTest is inspired by Catch2 (https://github.com/catchorg/Catch2),
/// under the BSL-1.0 license. The \c test_group and \c require macro in SkTest
/// corresponds to the \c TEST_CASE and \c REQUIRE macro in Catch2.

#ifndef sktest_test_hpp
#define sktest_test_hpp

#include <stddef.h> // NOLINT
#include <stdlib.h> // NOLINT

#include <sktest/registration.hpp>
#include <sktest/test_group.hpp>
#include <sktest/assertion.hpp>

// Let SkTest provide the main function if "USE_SKTEST_DEFAULT_MAIN_FUNCTION" is
// defined.
#ifdef USE_SKTEST_DEFAULT_MAIN_FUNCTION
int main/* NOLINT */([[maybe_unused]] int _argc,
                     [[maybe_unused]] char **_argv) {
  return sktest::RegistrationCenter::get_mutable().invoke_tests();
}
#endif

#endif /* sktest_test_hpp */