#ifndef _sktest_assertion_hpp
#define _sktest_assertion_hpp

#include <stdio.h>

#ifndef require
#define require(expr, description) \
  if (!(expr)) { \
    printf("%s:%d: REQUIRE(%s) failed\n", __FILE__, __LINE__, #expr); \
    return; \
  }
#endif

#endif /* _sktest_assertion_hpp */