#ifndef sktest_assertion_hpp
#define sktest_assertion_hpp

#include <sktest/registration.hpp>
#include <sktest/ansi_color.hpp>
#include <sktest/source_info.hpp>

#include <stdio.h>  // NOLINT
#include <string.h> // NOLINT

namespace sktest {
  class TestGroup;

  class Assertion {
   private:
    bool passed;
    char const *description;
    const SourceInfo info;

   public:
    Assertion(bool passed, char const *description,
              char const *file_name, size_t line_number)
      : passed(passed), description(description),
        info(file_name, line_number) {}

    virtual ~Assertion() = default;

    virtual auto print_report_if_failed() -> void {} // = 0;

    auto register_to(TestGroup &test_group) -> void; // NO NEED!
    auto submit_to_registration_center() -> Assertion &;

    [[nodiscard]]
    auto has_passed() const -> bool {
      return passed;
    }

    [[nodiscard]]
    auto get_description() const -> char const * {
      return description;
    }

    [[nodiscard]]
    auto get_file() const -> char const * {
      return info.get_file();
    }

    [[nodiscard]]
    auto get_line() const -> size_t {
      return info.get_line();
    }
  };

  class BooleanAssertion : public Assertion {
   private:
    const char *expression;
   public:
    BooleanAssertion(bool passed, const char *expression,
                    const char *description,
                    const char *file_name, size_t line_number)
      : Assertion(passed, description, file_name, line_number),
        expression(expression) {}

    [[nodiscard]]
    auto get_expression() const -> const char * {
      return expression;
    }
  };

  class IsTrueAssertion : public BooleanAssertion {
   public:
    using BooleanAssertion::BooleanAssertion;
  };

  class IsFalseAssertion : public BooleanAssertion {
   public:
    using BooleanAssertion::BooleanAssertion;
  };

  class EquivalenceAssertion : public Assertion {
   private:
    const char *left;
    const char *right;
   public:
    EquivalenceAssertion(bool passed, const char *left, const char *right,
                         const char *description,
                         const char *file_name, size_t line_number)
      : Assertion(passed, description, file_name, line_number),
        left(left), right(right) {}

    [[nodiscard]]
    auto get_left() const -> const char * {
      return left;
    }

    [[nodiscard]]
    auto get_right() const -> const char * {
      return right;
    }
  };

  class AreEqualAssertion : public EquivalenceAssertion {
   public:
    using EquivalenceAssertion::EquivalenceAssertion;
  };

  class AreNotEqualAssertion : public EquivalenceAssertion {
   public:
    using EquivalenceAssertion::EquivalenceAssertion;
  };

} // namespace sktest

#define sktest_overload_boolean_assert(_1, _2, _3, name, ...) name

#define sktest_boolean_assert_with_description(kind, condition, description)   \
  kind((condition), #condition, description, __FILE__, __LINE__)               \
    .submit_to_registration_center()                                           \
    .print_report_if_failed();

#define sktest_boolean_assert_without_description(kind, condition)             \
  kind((condition), #condition, /*description=*/"", __FILE__, __LINE__)        \
    .submit_to_registration_center()                                           \
    .print_report_if_failed()

#define sktest_boolean_assert(...)                                             \
  sktest_overload_boolean_assert(                                              \
    __VA_ARGS__,                                                               \
    sktest_boolean_assert_with_description,                                    \
    sktest_boolean_assert_without_description)(__VA_ARGS__)

#define assert_true(...) sktest_boolean_assert(sktest::IsTrueAssertion, __VA_ARGS__)

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

#endif /* sktest_assertion_hpp */