#ifndef sktest_test_group_hpp
#define sktest_test_group_hpp

#include <sktest/source_info.hpp>
#include <sktest/assertion.hpp>

#include <cstddef>
#include <cstring>
#include <vector>
#include <cassert>

namespace sktest {

  /// \brief The basic test collection in SkTest.
  ///
  /// \details A \c TestGroup is actually a invokable function that contains a
  /// set of tests. The tests can be automatically registered to
  /// \c RegistrationCenter by \c test_group macro. You should not use this
  /// struct directly.
  struct TestGroup {
   private:
    char const *description;
    SourceInfo info;
    void(*test_function)();

    std::vector<Assertion> assertions {};

   public:
    TestGroup(char const *description, void(*test_function)(),
              char const *file_name, size_t line_number) noexcept
      : description(description), test_function(test_function),
        info(file_name, line_number) {};

    auto push_assertion(Assertion assertion) noexcept -> void {
      assertions.push_back(std::move(assertion));
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

    [[nodiscard]]
    auto get_assertions() const -> const std::vector<Assertion> & {
      return assertions;
    }

    void invoke() const {
      assert(assertions.empty() && "cannot invoke a test group more than once");
      test_function();
    }
  };
} // namespace sktest

#define sktest_name_mangling(name, line) name##line
#define sktest_test_group_impl(description, line, file)                        \
  static void sktest_name_mangling(sktest_, line)();                           \
  namespace {                                                                  \
    sktest::Registrar sktest_name_mangling(sktest_registrar, line) (           \
      description,                                                             \
      &sktest_name_mangling(sktest_, line),                                    \
      file,                                                                    \
      size_t(line)                                                             \
    );                                                                         \
  }                                                                            \
  static void sktest_name_mangling(sktest_, line)()


// `__LINE__` is used to generate unique identifiers for each test group. Each
// test group is a static function internally, which is not visible to other
// files. So `__LINE__` is good enough for now, and do not need `__COUNTER__`.

/// \brief Define a test group with the given description.
///
/// \code
/// test_group ("test operator '+' for integer type") {
///     assert_equal(1 + 1, 2, "1 + 1 does not equal 2");
///     assert_equal(2 + 2, 4, "2 + 2 does not equal 4");
/// }
/// \endcode
///
/// Note that \c test_group is a keyword-like macro (looks like \c if, \c for,
/// etc.), you should consider leaving a space before the parentheses.
///
/// \code
/// test_group ("...") { ... }
/// //        ^ Good
/// test_group("...") { ... }
/// //        ^ Bad
/// \endcode
///
/// \param description Description for the test group. It better be a string
/// literal, I haven't checked memory safety for other situations.
#define test_group(description)                                                \
  sktest_test_group_impl(description, __LINE__, __FILE__)

#endif /* sktest_test_group_hpp */
