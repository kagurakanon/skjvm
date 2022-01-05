#ifndef sktest_registration_hpp
#define sktest_registration_hpp

#include <sktest/utilities.hpp>
#include <sktest/test_group.hpp>
#include <sktest/ansi_color.hpp>

#include <stddef.h> // NOLINT
#include <stdio.h>  // NOLINT
#include <assert.h> // NOLINT

namespace sktest {
  /// \brief Registration center of all test groups.
  ///
  /// This is a singleton class that is used to register all test groups. It
  /// will be initialized by the main function (provide by SkTest)
  /// automatically.
  class RegistrationCenter : private NonCopyable {
   private:
    TestGroup *test_groups{nullptr};
    size_t size{0};
    size_t capacity;
    size_t current_test_group{0};

    static auto get_instance_pointer() -> RegistrationCenter * {
      static RegistrationCenter *instance = nullptr;
      if (instance == nullptr) {
        instance = new RegistrationCenter();
      }
      return instance;
    }

    static constexpr size_t default_capacity = 16;

    auto sort_tests() -> void {
      qsort(test_groups, size, sizeof(TestGroup), &compare_test_groups);
    }

   public:
    RegistrationCenter() noexcept : capacity(default_capacity) {
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

    [[maybe_unused]] // This is used in the main function, which is defined
                     // with `USE_SKTEST_DEFAULT_MAIN_FUNCTION` macro. Static
                     // analysis may misreport unused function errors, we use
                     // `[[maybe_unused]]` attribute to suppress this warning.
    auto invoke_tests() -> int {
      assert(current_test_group == 0 && "cannot invoke tests more than once");

      sort_tests();

      size_t total_test_group_count  = 0;
      size_t passed_test_group_count = 0;
      size_t total_assertion_count   = 0;
      size_t passed_assertion_count  = 0;

      for (; current_test_group < size; ++current_test_group) {
        get_current_test_group().invoke();

        total_test_group_count += 1;
        if (get_current_test_group().all_assertion_passed()) {
          passed_test_group_count += 1;
        }

        total_assertion_count +=
          get_current_test_group().get_total_assertion_count();
        passed_assertion_count +=
          get_current_test_group().get_passed_assertion_count();
      }

      print_statistics(
        total_test_group_count, passed_test_group_count,
        total_assertion_count, passed_assertion_count);

      return total_assertion_count == passed_assertion_count ? 0 : 1;
    }

    static auto print_statistics(size_t total_test_group_count,
                          size_t passed_test_group_count,
                          size_t total_assertion_count,
                          size_t passed_assertion_count) -> void {
      if (passed_assertion_count == total_assertion_count) {
        puts(bold_green("test passed:"));
      } else {
        puts(bold_red("tests failed:"));
      }

      double pass_rate = double(passed_assertion_count)
                    / // ------------------------------
                         double(total_assertion_count);

      constexpr unsigned int pass_rate_bar_width = 32;

      auto red_part_width =
        (unsigned int)((1.0 - pass_rate) * double(pass_rate_bar_width));

      // When the pass rate is close to but not equal to 1. `red_bar_count` may
      // be equal to 0 after rounding, making it look like all the tests
      // passed. We need to manually set `red_bar_count` to 1 in this case.
      if (red_part_width == 0 and
          passed_assertion_count != total_assertion_count) {
        red_part_width = 1;
      }

      unsigned int green_part_width = pass_rate_bar_width - red_part_width;

      constexpr int percentage_base = 100;
      printf("  [" green("%.*s") red("%.*s") "] %.1f%%\n",
             green_part_width, "========================================",
             red_part_width,   "========================================",
             pass_rate * percentage_base);

      printf("  " bold("test group:") "   "
             green("%zu passed") ", " red("%zu failed") ", " "%zu total\n",
             passed_test_group_count,
             total_test_group_count - passed_test_group_count,
             total_test_group_count);

      printf("  " bold("assertion:") "    "
             green("%zu passed") ", " red("%zu failed") ", " "%zu total\n",
             passed_assertion_count,
             total_assertion_count - passed_assertion_count,
             total_assertion_count);
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

#endif /* sktest_registration_hpp */
