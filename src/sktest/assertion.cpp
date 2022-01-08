#include <sktest/assertion.hpp>
#include <sktest/registration.hpp>
#include <sktest/test_group.hpp>

namespace sktest {
  auto Assertion::submit_to_registration_center() -> Assertion & {
    RegistrationCenter::get_current_test_group().push_assertion(*this);
    return *this;
  }

  auto IsTrueAssertion::print_report_if_failed() const -> void {
    if (has_passed()) { return; }

    printf(bold_red("error:") " test failed at %s:%zu\n",
           info.get_file(), info.get_line());
    printf("  " bold("test group:") "   %s\n", test_group.get_description());
    printf("  " bold("condition:") "    assert_true( " blue("%s") " )\n",
           condition);

    if (strcmp(description, "") != 0) {
      printf("  " bold("description:") "  %s\n", description);
    }
  }

  auto IsFalseAssertion::print_report_if_failed() const -> void {
    if (has_passed()) { return; }

    printf(bold_red("error:") " test failed at %s:%zu\n",
           info.get_file(), info.get_line());
    printf("  " bold("test group:") "   %s\n", test_group.get_description());
    printf("  " bold("condition:") "    assert_true( " blue("%s") " )\n",
           condition);

    if (strcmp(description, "") != 0) {
      printf("  " bold("description:") "  %s\n", description);
    }
  }

  auto AreEqualAssertion::print_report_if_failed() const -> void {
    if (has_passed()) { return; }

    printf(bold_red("error:") " test failed at %s:%zu\n",
           info.get_file(), info.get_line());
    printf("  " bold("test group:") "   %s\n", test_group.get_description());
    printf(
      "  " bold("condition:") "    assert_equal(\n"
      "                  left  = " blue("%s") " ,\n"
      "                  right = " blue("%s") " ,\n"
      "                )\n", left, right);

    if (strcmp(description, "") != 0) {
      printf("  " bold("description:") "  %s\n", description);
    }
  }

  auto AreNotEqualAssertion::print_report_if_failed() const -> void {
    if (has_passed()) { return; }

    printf(bold_red("error:") " test failed at %s:%zu\n",
           info.get_file(), info.get_line());
    printf("  " bold("test group:") "   %s\n", test_group.get_description());
    printf(
      "  " bold("condition:") "    assert_not_equal(\n"
      "                  left  = " blue("%s") " ,\n"
      "                  right = " blue("%s") " ,\n"
      "                )\n", left, right);

    if (strcmp(description, "") != 0) {
      printf("  " bold("description:") "  %s\n", description);
    }
  }
} // namespace sktest
