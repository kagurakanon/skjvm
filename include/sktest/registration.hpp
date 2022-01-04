#ifndef _sktest_registration_hpp
#define _sktest_registration_hpp

#include <sktest/utilities.hpp>
#include <sktest/test_group.hpp>
#include <sktest/ansi_color.hpp>

#include <stddef.h>
#include <stdio.h>
#include <assert.h>

namespace sktest {
  /// \brief Registration center of all test groups.
  ///
  /// This is a singleton class that is used to register all test groups. It
  /// will be initialized by the main function (provide by SkTest)
  /// automatically.
  class RegistrationCenter : private NonCopyable {
   private:
    TestGroup *test_groups;
    size_t size;
    size_t capacity;
    size_t current_test_group;

    static auto get_instance_pointer() -> RegistrationCenter * {
      static RegistrationCenter *instance = nullptr;
      if (instance == nullptr)
        instance = new RegistrationCenter();
      return instance;
    }

    static constexpr size_t default_capacity = 16;

    auto sort_tests() -> void {
      qsort(test_groups, size, sizeof(TestGroup), &compare_test_groups);
    }

   public:
    RegistrationCenter() noexcept
      : test_groups(nullptr), size(0), capacity(default_capacity),
        current_test_group(0) {
      test_groups = (TestGroup *)malloc(sizeof(TestGroup) * capacity);
    }

    ~RegistrationCenter() noexcept override {
      free(test_groups);
    }

    auto register_test(TestGroup group) -> void {
      if (size == capacity) {
        capacity *= 2;
        test_groups =
            (TestGroup *)realloc(test_groups, sizeof(TestGroup) * capacity);
      }
      test_groups[size++] = group;
    }

    auto invoke_tests() -> int {
      assert(current_test_group == 0 && "cannot invoke tests more than once");

      size_t total_test_group_count  = 0;
      size_t passed_test_group_count = 0;
      size_t total_assertion_count   = 0;
      size_t passed_assertion_count  = 0;

      for (; current_test_group < size; ++current_test_group) {
        get_current_test_group().invoke();

        total_test_group_count += 1;
        if (get_current_test_group().all_assertion_passed())
          passed_test_group_count += 1;

        total_assertion_count +=
          get_current_test_group().get_total_assertion_count();
        passed_assertion_count +=
          get_current_test_group().get_passed_assertion_count();
      }

      if (passed_assertion_count == total_assertion_count)
        printf(BOLD_GREEN "test passed:" RESET "\n");
      else
        printf(BOLD_RED "tests failed:" RESET "\n");

      constexpr unsigned int bar_width = 35;
      double pass_rate = double(passed_assertion_count)
                    / // ------------------------------
                         double(total_assertion_count);
      unsigned int red_bar_count = (1 - pass_rate) * bar_width;

      // Red part of the bar should not be 0 if pass_rate is not exactly 1.
      if (passed_assertion_count != total_assertion_count && red_bar_count == 0)
        red_bar_count = 1;

      unsigned int green_bar_count = bar_width - red_bar_count;

      printf("  [" GREEN);
      for (auto i = 0; i < green_bar_count; ++i) { printf("="); }
      printf(RESET);

      printf(RED);
      for (auto i = 0; i < red_bar_count; ++i) { printf("="); }
      printf(RESET "] ");

      printf("%.0f%%\n", pass_rate * 100);

      #define statistical_information                                          \
        GREEN "%zu passed" RESET ", "                                          \
        RED   "%zu failed" RESET ", "                                          \
              "%zu total"  RESET "\n"                                          \

      printf("  " BOLD "test group:" RESET "   " statistical_information,
             passed_test_group_count,
             total_test_group_count - passed_test_group_count,
             total_test_group_count);

      printf("  " BOLD "assertion:" RESET "    " statistical_information,
             passed_assertion_count,
             total_assertion_count - passed_assertion_count,
             total_assertion_count);

      #undef statistical_information

      return total_assertion_count == passed_assertion_count ? 0 : 1;
    }

    [[nodiscard]]
    auto get_current_test_group() const -> TestGroup & {
      return test_groups[current_test_group];
    }

    /// Get the const reference of the singleton instance of the
    /// \c RegistrationCenter.
    static auto get_immutable() -> RegistrationCenter const & {
      return *get_instance_pointer();
    }

    /// Get the singleton instance of the \c RegistrationCenter with a mutable
    /// reference.
    static auto get_mutable() -> RegistrationCenter & {
      return *get_instance_pointer();
    }
  };

  /// \brief Register a test group to \c RegistrationCenter while initializing.
  ///
  /// This class's initializer will be called in \c test_group macro. It's an
  /// idiomatic way to performing registration code in global scope.
  class Registrar {
   public:
    Registrar(char const *name, void(*test)(),
              char const *file_name, size_t line_number) noexcept {
      TestGroup group(name, test, file_name, line_number);
      RegistrationCenter::get_mutable().register_test(group);
    }
    ~Registrar() noexcept = default;
  };
}

#endif /* _sktest_registration_hpp */
