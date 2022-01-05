// NOTE: `stdio.h` and `cstdio` are different, the former is the C I/O library,
// and the latter is part of the C++ standard library, which is usually a better
// choice. However, I prefer not to use (and link) STL, so I'm using the former
// instead here.
#include <stdio.h> // NOLINT

auto main() -> int {
  printf("Hello, world!\n");
  return 0;
}