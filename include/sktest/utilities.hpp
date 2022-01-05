#ifndef sktest_utilities_hpp
#define sktest_utilities_hpp

namespace sktest {
  /// \brief Abstract class for non-copyable objects, delete copy constructor
  /// and assignment operator.
  ///
  /// This is mainly used for singletons like \c RegistrationCenter and its
  /// elements.
  class NonCopyable {
   public:
    NonCopyable(NonCopyable const&)            = delete;
    NonCopyable(NonCopyable &&)                = delete;
    NonCopyable &operator=(NonCopyable const&) = delete;
    NonCopyable &operator=(NonCopyable &&)     = delete;

  protected:
    NonCopyable() noexcept = default;
    virtual ~NonCopyable() noexcept = default;
  };
}

#endif /* sktest_utilities_hpp */