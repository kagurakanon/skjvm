#ifndef _sktest_assertion_hpp
#define _sktest_assertion_hpp

#include <stdio.h>

#ifndef sktest_require_impl
#define sktest_require_impl(expr, description, file, line)                     \
  if (!(expr)) {                                                               \
    printf("\033[31;1;1merror:\033[0m test failed at %s:%  d\n", file, line);  \
    printf("  require( \033[34m%s\033[0m )\n", #expr);                         \
    printf("  ^^^^^^^%s\n", description);                                      \
  }
#endif

#ifndef sktest_require_with_description
#define sktest_require_with_description(expr, description)                     \
  sktest_require_impl(expr, description, __FILE__, __LINE__)
#endif

#ifndef sktest_require_without_description
#define sktest_require_without_description(expr)                               \
  sktest_require_impl(expr, "", __FILE__, __LINE__)
#endif

#ifndef sktest_get_macro
#define sktest_get_macro(_1, _2, name, ...) name
#endif

#ifndef require
#define require(...)                                                           \
  sktest_get_macro(__VA_ARGS__,                                                \
                   sktest_require_with_description,                            \
                   sktest_require_without_description)(__VA_ARGS__)
#endif

#endif /* _sktest_assertion_hpp */