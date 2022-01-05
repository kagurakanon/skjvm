Shinkai JVM
===========

> **WIP:** This project is still in early development.

Shinkai JVM is an experimental Java compiler and Java virtual machine (JVM)
written in modern C++, for research purposes only.

Installation
------------

> **Note:** Currently only macOS Monterey and macOS Bir Sur are supported.
> We will support other OS when the project is more mature. The planned list
> includes older macOS, Windows 10/11, and Linux (in particular, Debian).

Environmental requirements:

- [macOS](https://www.apple.com/macos/monterey/),
  version &ge; 11.0, < 13;
- [CMake](https://cmake.org),
  version &ge; 3.20;
- [GNU Make](https://www.gnu.org/software/make/),
  version &ge; 3.0 (ignore it if you know how to use other build systems);
- [Clang](https://clang.llvm.org)
  Apple's distribution (aka. Apple Clang), version &ge; 13.0.0;

Run the following script in shell:

```shell
git clone https://github.com/kkshinkai/skjvm.git
cd skjvm

cmake -S . -B build -G "Unix Makefiles"
cmake --build build
./build/bin/java
```

or use [`./build.sh`](./build.sh) directly.

```shell
chmod +x ./build.sh
./build.sh build
./build/bin/java
```

Goals
-----

Here are the main goals of Shinkai JVM:

- [ ] A largely specifications-compliant Java virtual machine (JVM). The most
  features of Java 8 will be implemented, except for the Jar (aka. Zip)
  handling, because I don't want to introduce the Zip library dependencies;
- [ ] A Java-like language compiler that generates JVM bytecode;
- [ ] A set of research-purposes garbage collectors;

However, this project is not just about Java, but also contains some additional
works as follows:

- [x] A minimalist testing framework (Done, see also
  [SkTest](./include/sktest/test.hpp));
- [ ] A low-level C++ core library, include collections, smart pointers, and
  other utilities, without using STL;
- [ ] A small Unicode string library (not as fully functional as ICU) that
  provide basic Unicode operations.
- [ ] A wrapper for various operating systems, including macOS (BSD), Linux, and
  Windows. Provide I/O support, threading, file system, etc.

The Shinkai JVM does not link to the C++ standard library, as an experiment.

License
-------

This project is licensed under the terms of the Unlicense, see
[LICENSE.txt](./LICENSE.txt) for details.
