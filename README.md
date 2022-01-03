Shinkai JVM
===========

Shinkai JVM is an experimental Java compiler and Java virtual machine (JVM)
written in modern C++, for research purposes only. Here are the main goals:

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
