#ifndef _sktest_assertion_hpp
#define _sktest_assertion_hpp

#include <stdio.h>

#ifndef sktest_require_impl
#define sktest_require_impl(expr, description, file, line)                     \
  if (!(expr)) {                                                               \
    printf("\033[31;1;1merror:\033[0m test failed at %s:%d\n", file, line);    \
    printf(" \033[37m%d |\033[0m  require(\033[34m%s\033[0m)\n", line, #expr); \
    printf(" \033[37m%d |\033[0m  ^^^^^^^%s\n", line + 1, description);        \
  }
#endif

#ifndef require
#define require(expr, description)                                             \
  sktest_require_impl(expr, description, __FILE__, __LINE__)
#endif

#endif /* _sktest_assertion_hpp */