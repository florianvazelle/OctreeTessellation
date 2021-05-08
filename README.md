# OctreeTessellation

![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/florianvazelle/OctreeTessellation/build/main?label=Windows%20%7C%20Linux&logo=github)

## Building

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -B build
cmake --build build
./build/bin/OctreeTessellation
```

## Dependencies

- C++20 compiler :
  - Visual Studio 2019
  - GCC 8+ or Clang 8+
- [CMake](https://cmake.org/) for build system creation (>= 3.8)
- [Conan](https://conan.io/) for install packages (>= 1.0)

## References

### Octree

- [C Implementation](https://stackoverflow.com/questions/5963954/fast-templated-c-octree-implementation#8423694)
- [As LOD System](https://gamedev.stackexchange.com/questions/184631/using-octrees-as-lod-system)

### OpenGL Wiki Shader

- [Tessellation Control](https://www.khronos.org/opengl/wiki/Tessellation_Control_Shader)
- [Tessellation](https://www.khronos.org/opengl/wiki/Tessellation)

### Tessellation Tutorial

- [Shader Example](http://www.ogldev.org/www/tutorial30/tutorial30.html)