#include <sktest/registration.hpp>
#include <sktest/test_group.hpp>

namespace sktest {

  auto RegistrationCenter::sort_tests() -> void {
    std::sort(test_groups.begin(), test_groups.end(), [](auto lhs, auto rhs) {
      int compare_name = strcmp(lhs.get_file(), rhs.get_file());
      if (compare_name != 0) {
        return compare_name;
      }
      return int(lhs.get_line()) - int(rhs.get_line());
    });
  }

  auto RegistrationCenter::push_test_group(TestGroup group) -> void {
    test_groups.push_back(std::move(group));
  }

  auto RegistrationCenter::invoke_tests() -> int {
    assert(current_test_group == 0 && "cannot invoke tests more than once");

    sort_tests();

    size_t total_test_group_count  = 0;
    size_t passed_test_group_count = 0;
    size_t total_assertion_count   = 0;
    size_t passed_assertion_count  = 0;

    for (; current_test_group < test_groups.size(); ++current_test_group) {
      ++total_test_group_count;

      auto &test_group = get_current_test_group();
      test_group.invoke();

      bool has_passed = true;
      for (const auto &assertion : test_group.get_assertions()) {
        ++total_assertion_count;

        if (assertion.has_passed()) {
          ++passed_assertion_count;
        } else {
          has_passed = false;
        }
      }

      if (has_passed) {
        ++passed_test_group_count;
      }
    }

    print_statistics(
      total_test_group_count, passed_test_group_count,
      total_assertion_count, passed_assertion_count);

    return total_assertion_count == passed_assertion_count ? 0 : 1;
  }

  Registrar::Registrar(const char *name, void (*test)(),
                       const char *file_name, size_t line_number) noexcept {
    TestGroup group(name, test, file_name, line_number);
    RegistrationCenter::get_mutable().push_test_group(group);
  }
}