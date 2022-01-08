#include <sktest/assertion.hpp>
#include <sktest/registration.hpp>
#include <sktest/test_group.hpp>

namespace sktest {
  auto Assertion::register_to(TestGroup &test_group) -> void {
    RegistrationCenter::get_mutable()
      .get_current_test_group()
      .push_assertion(*this);
  }

  auto Assertion::submit_to_registration_center() -> Assertion & {
    auto &test_group = RegistrationCenter::get_mutable()
      .get_current_test_group();
    register_to(test_group);
    return *this;
  }
} // namespace sktest
