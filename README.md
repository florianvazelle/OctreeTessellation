# OctreeTessellation

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

## References

### Octree

- [C Implementation](https://stackoverflow.com/questions/5963954/fast-templated-c-octree-implementation#8423694)
- [As LOD System](https://gamedev.stackexchange.com/questions/184631/using-octrees-as-lod-system)

### OpenGL Wiki Shader

- [Tessellation Control](https://www.khronos.org/opengl/wiki/Tessellation_Control_Shader)
- [Tessellation](https://www.khronos.org/opengl/wiki/Tessellation)

### Tessellation Tutorial

- [Shader Example](http://www.ogldev.org/www/tutorial30/tutorial30.html)