#ifndef _sktest_test_hpp
#define _sktest_test_hpp

#include <stddef.h>
#include <stdlib.h>

namespace sktest {
  namespace detail {
    class NonCopyable {
      NonCopyable(NonCopyable const&)            = delete;
      NonCopyable(NonCopyable &&)                = delete;
      NonCopyable &operator=(NonCopyable const&) = delete;
      NonCopyable &operator=(NonCopyable &&)     = delete;

    protected:
      NonCopyable() noexcept = default;
      virtual ~NonCopyable() noexcept = default;
    };
  } // namespace _detail

  struct TestCase {
   private:
    char const *name;
    void(*test)();
   public:
    TestCase(char const *name, void(*test)()) noexcept : test(test) {};
    void invoke() const { test(); }
  };

  class RegistryHub : private detail::NonCopyable {
   private:
    TestCase *test_cases;
    size_t size;
    size_t capacity;

    static auto get_instance_pointer() -> RegistryHub * {
      static RegistryHub *instance = nullptr;
      if (instance == nullptr)
        instance = new RegistryHub();
      return instance;
    }

   public:
    RegistryHub() noexcept : test_cases(nullptr), size(0), capacity(32) {
      test_cases = (TestCase *)malloc(sizeof(TestCase) * capacity);
    }

    ~RegistryHub() noexcept {
      free(test_cases);
    }

    void register_test(TestCase test_case) {
      if (size == capacity) {
        capacity *= 2;
        test_cases =
          (TestCase *)realloc(test_cases, sizeof(TestCase) * capacity);
      }
      test_cases[size++] = test_case;
    }

    void invoke_all_tests() const {
      for (size_t i = 0; i < size; ++i) {
        test_cases[i].invoke();
      }
    }

    // Get the const reference of the singleton instance of the registry hub.
    static auto get_immutable() -> RegistryHub const & {
      return *get_instance_pointer();
    }

    // Get the singleton instance of the registry hub with a mutable reference.
    static auto get_mutable() -> RegistryHub & {
      return *get_instance_pointer();
    }
  };
} // namespace sktest

// Let SkTest provide the main function.
#ifdef USE_SKTEST_DEFAULT_MAIN_FUNCTION
int main(int argc, char **argv) {
  sktest::RegistryHub::get_immutable().invoke_all_tests();
  return 0;
}
#endif

#endif /* _sktest_test_hpp */