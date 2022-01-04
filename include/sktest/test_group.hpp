#ifndef _sktest_test_group_hpp
#define _sktest_test_group_hpp

#include <stddef.h>

namespace sktest {
  struct TestInfo {
   private:
    char const *file_name;
    size_t line_number;
   public:
    TestInfo(char const *file_name, size_t line_number) noexcept
      : file_name(file_name), line_number(line_number) {}

    [[nodiscard]] char const *get_file_name() const { return file_name; }
    [[nodiscard]] size_t get_line_number() const { return line_number; }
  };

  /// \brief The basic test collection in SkTest.
  ///
  /// A \c TestGroup is actually a invokable function that contains a set of
  /// tests. The tests can be automatically registered to \c RegistrationCenter
  /// by \c test_group macro. You should not use this struct directly.
  struct TestGroup {
   private:
    char const *name;
    void(*test_function)();
   public:
    TestGroup(char const *name, void(*test_function)()) noexcept
      : name(name), test_function(test_function) {};
    void invoke() const { test_function(); }
  };
} // namespace sktest

#ifndef test_group

#define sktest_name_mangling(name, line) name##line
#define sktest_test_group_impl(description, line)                              \
  static void sktest_name_mangling(sktest_, line)();                           \
  namespace {                                                                  \
    sktest::Registrar sktest_name_mangling(sktest_registrar, line) (           \
      description,                                                             \
      &sktest_name_mangling(sktest_, line)                                     \
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
///     require(1 + 1 == 2, "1 + 1 does not equal 2");
///     require(2 + 2 == 4, "2 + 2 does not equal 4");
/// }
/// \endcode
///
/// Note that \c test_group is a keyword-like macro (looks like `if`, `for`,
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
#define test_group(description) sktest_test_group_impl(description, __LINE__)

#endif // test_group

#endif /* _sktest_test_group_hpp */
