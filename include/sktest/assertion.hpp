#ifndef sktest_assertion_hpp
#define sktest_assertion_hpp

#include <sktest/registration.hpp>
#include <sktest/ansi_color.hpp>
#include <sktest/source_info.hpp>

#include <cstdio>
#include <cstring>

namespace sktest {
  class TestGroup;

  class Assertion {
   protected:
    bool passed;
    char const *description;
    const SourceInfo info;
    const TestGroup &test_group;

   public:
    Assertion(bool passed, char const *description,
              char const *file_name, size_t line_number)
      : passed(passed), description(description),
        info(file_name, line_number),
        test_group(RegistrationCenter::get_current_test_group()) {}

    virtual ~Assertion() = default;

    virtual auto print_report_if_failed() const -> void {} // = 0;

    auto submit_to_registration_center() -> Assertion &;

    [[nodiscard]]
    auto has_passed() const -> bool {
      return passed;
    }

    [[nodiscard]]
    auto get_test_group() const -> const TestGroup & {
      return test_group;
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
   protected:
    const char *condition;
   public:
    BooleanAssertion(bool passed, const char *condition,
                    const char *description,
                    const char *file_name, size_t line_number)
      : Assertion(passed, description, file_name, line_number),
        condition(condition) {}

    [[nodiscard]]
    auto get_condition() const -> const char * {
      return condition;
    }
  };

  class IsTrueAssertion : public BooleanAssertion {
   public:
    using BooleanAssertion::BooleanAssertion;

    auto print_report_if_failed() const -> void override;
  };

  class IsFalseAssertion : public BooleanAssertion {
   public:
    using BooleanAssertion::BooleanAssertion;

    auto print_report_if_failed() const -> void override;
  };

  class EquivalenceAssertion : public Assertion {
   protected:
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

    auto print_report_if_failed() const -> void override;
  };

  class AreNotEqualAssertion : public EquivalenceAssertion {
   public:
    using EquivalenceAssertion::EquivalenceAssertion;

    auto print_report_if_failed() const -> void override;
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

/// \brief Creates an assertion that the expression is true.
///
/// \example The assertion can have a description, which will be printed on
/// failure.
/// \code
/// test_group ("example test group") {
///     assert_true(1 == 1);
///     assert_true(1 == 2, "1 is not equal to 2");
/// }
/// \endcode
#define assert_true(...)                                                       \
  sktest_boolean_assert(sktest::IsTrueAssertion, __VA_ARGS__)

/// \brief Creates an assertion that the expression is false.
///
/// \example The assertion can have a description, which will be printed on
/// failure.
/// \code
/// test_group ("example test group") {
///     assert_false(1 == 2);
///     assert_false(1 == 1, "1 is equal to 1");
/// }
/// \endcode
#define assert_false(...)                                                      \
  sktest_boolean_assert(sktest::IsFalseAssertion, __VA_ARGS__)

#define sktest_overload_equivalence_assert(_1, _2, _3, _4, _5, name, ...) name

#define sktest_equal_assert_with_description(kind, op, left, right, desc)      \
  kind((left) op (right), #left, #right, desc, __FILE__, __LINE__)             \
    .submit_to_registration_center()                                           \
    .print_report_if_failed();

#define sktest_equal_assert_without_description(kind, op, left, right)         \
  kind((left) op (right), #left, #right, "", __FILE__, __LINE__)               \
    .submit_to_registration_center()                                           \
    .print_report_if_failed()

#define sktest_equal_assert(...)                                               \
  sktest_overload_equivalence_assert(                                          \
    __VA_ARGS__,                                                               \
    sktest_equal_assert_with_description,                                      \
    sktest_equal_assert_without_description)(__VA_ARGS__)


/// \brief Creates an assertion that two expressions are equal.
///
/// \example The assertion can have a description, which will be printed on
/// failure.
/// \code
/// test_group ("example test group") {
///     assert_equal(1, 1);
///     assert_equal(1, 2, "1 is not equal to 2");
/// }
/// \endcode
#define assert_equal(...)                                                      \
  sktest_equal_assert(sktest::AreEqualAssertion, ==, __VA_ARGS__)

/// \brief Creates an assertion that two expressions are not equal.
///
/// \example The assertion can have a description, which will be printed on
/// failure.
/// \code
/// test_group ("example test group") {
///     assert_not_equal(1, 2);
///     assert_not_equal(1, 2, "1 is equal to 1");
/// }
/// \endcode
#define assert_not_equal(...)                                                  \
  sktest_equal_assert(sktest::AreNotEqualAssertion, !=, __VA_ARGS__)

#endif /* sktest_assertion_hpp */