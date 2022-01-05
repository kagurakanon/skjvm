#ifndef sktest_assertion_hpp
#define sktest_assertion_hpp

#include <sktest/registration.hpp>
#include <sktest/ansi_color.hpp>

#include <stdio.h>
#include <string.h>

namespace sktest {
  class Assertion {
   private:
    bool has_passed;
    char const *description;
    char const *expression;
    char const *file_name;
    size_t line_number;
   public:
    Assertion(bool passed,
              char const *description, char const *expression,
              char const *file_name, size_t line_number)
      : has_passed(passed),
        description(description), expression(expression),
        file_name(file_name), line_number(line_number) {
      if (!has_passed) {
        printf(bold_red("error:") " test failed at %s:%zu\n",
               file_name, line_number);
        printf("  " bold("test group:") "   %s\n",
               RegistrationCenter::get_immutable().get_current_test_group()
                                                  .get_description());
        printf("  " bold("expression:") "   require( " blue("%s") " )\n",
               expression);
        if (strcmp(description, "") != 0)
          printf("  " bold("description:") "  %s\n", description);
      }
      RegistrationCenter::get_mutable().get_current_test_group()
                                       .add_assertion(has_passed);
    }
  };
} // namespace sktest

#ifndef sktest_require_impl
#define sktest_require_impl(expr, description, file, line)                     \
  sktest::Assertion((expr), description, #expr, file, line)
#endif

#ifndef sktest_require_with_description
#define sktest_require_with_description(expr, description)                     \
  sktest_require_impl(expr, description, __FILE__, __LINE__)
#endif

#ifndef sktest_require_without_description
#define sktest_require_without_description(expr)                               \
  sktest_require_impl(expr, "", __FILE__, __LINE__)
#endif

#ifndef sktest_get_macro
#define sktest_get_macro(_1, _2, name, ...) name
#endif

#ifndef require

/// \brief Creates an assertion that the expression is true.
///
/// \example The assertion can have a description, which will be printed on
/// failure.
/// \code
/// test_group ("example test group") {
///     require(1 == 1);
///     require(1 == 2, "1 is not equal to 2");
/// }
/// \endcode
#define require(...)                                                           \
  sktest_get_macro(__VA_ARGS__,                                                \
                   sktest_require_with_description,                            \
                   sktest_require_without_description)(__VA_ARGS__)
#endif

#endif /* sktest_assertion_hpp */