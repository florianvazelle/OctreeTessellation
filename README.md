# cpp-template

## Building

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -B build
cmake --build build
./build/bin/OctreeTessellation
```

## Dependencies

- C++11 compiler :
  - Visual Studio 2016
  - GCC 5+ or Clang 5+
- [CMake](https://cmake.org/) for build system creation (>= 3.8)
- [Conan](https://conan.io/) for install packages (>= 1.0)
