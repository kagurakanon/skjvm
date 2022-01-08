#ifndef sktest_source_info_hpp
#define sktest_source_info_hpp

namespace sktest {

  /// \brief Position information of an assertion, including file name and line
  ///  number.
  struct SourceInfo {
   private:
    char const *file_name;
    size_t line_number;

   public:
    SourceInfo(char const *file_name, size_t line_number) noexcept
      : file_name(file_name), line_number(line_number) {}

    [[nodiscard]]
    auto get_file() const -> char const * {
      return file_name;
    }

    [[nodiscard]]
    auto get_line() const -> size_t {
      return line_number;
    }
  };

} // namespace sktest

#endif /* sktest_source_info_hpp */
