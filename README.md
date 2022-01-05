Shinkai JVM
===========

Shinkai JVM is an experimental Java compiler and Java virtual machine (JVM)
written in modern C++, for research purposes only.

Installation
------------

> \[&#x2139;\] Currently only macOS Monterey and macOS Bir Sur are supported.
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

Here are the main goals:

- Implement a largely specifications-compliant Java virtual machine. The basic
  features of Java 8 will be implemented, but explicitly except for the handling
  of Jars (aka. Zip files).
- Implement a Java-like language compiler (perhaps a reduced version of Swift)
  that generates JVM bytecode.
- Implement a set of portable garbage collectors based on different garbage
  collection algorithms.

However, this project is not just about Java, but also contains some additional
works:

- A low-level C++ collection template library, include dynamic array, hash
  table, linked list, tuples, maybe type, either type, etc. and related
  algorithms, without using STL.
- A minimal Unicode string library (not the ICU kind) that provide only some
  basic Unicode operations.
- An efficient language support library. Provide some common low-level tools
  like tagged union pointer, smart pointers, etc.
- A cross-platform wrapper for various operating systems, including macOS,
  Linux, and Windows. Provide basic I/O support, threading, file system, etc.

License
-------

This project is licensed under the terms of the Unlicense, see
[LICENSE.txt](./LICENSE.txt) for details.
