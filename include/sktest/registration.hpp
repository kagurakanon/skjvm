#ifndef _sktest_registration_hpp
#define _sktest_registration_hpp

#include <sktest/utilities.hpp>
#include <sktest/test_group.hpp>

#include <stddef.h>

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

    static auto get_instance_pointer() -> RegistrationCenter * {
      static RegistrationCenter *instance = nullptr;
      if (instance == nullptr)
        instance = new RegistrationCenter();
      return instance;
    }

    static constexpr size_t default_capacity = 16;

   public:
    RegistrationCenter() noexcept
      : test_groups(nullptr), size(0), capacity(default_capacity) {
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

    auto invoke_all_tests() const -> void {
      for (size_t i = 0; i < size; ++i) {
        test_groups[i].invoke();
      }
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
    Registrar(char const *name, void(*test)()) noexcept {
      RegistrationCenter::get_mutable().register_test(TestGroup(name, test));
    }
    ~Registrar() noexcept = default;
  };
}

#endif /* _sktest_registration_hpp */
