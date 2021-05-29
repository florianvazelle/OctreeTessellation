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

- C++20 compiler (to use [Mathematical constants](https://en.cppreference.com/w/cpp/numeric/constants)) :
  - VS 2019 16.5
  - GCC 10+ or Clang 11+
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

### Papers

- [Adaptive GPU Tessellationwith Compute Shaders](https://onrendering.com/data/papers/isubd/isubd.pdf)
- [A Real-Time Procedural Universe](https://www.gamasutra.com/view/feature/2511/a_realtime_procedural_universe_.php?print=1)
- [Efficient GPU Rendering of Subdivision Surfaces using Adaptive Quadtrees](https://graphics.stanford.edu/~niessner/papers/2016/4subdiv/brainerd2016efficient.pdf)
- [Terrain Tessellation with Geomipmapping](http://users.csc.calpoly.edu/~zwood/teaching/csc572/final15/rpeder/index.html)

### Books

- [ShaderX](https://www.realtimerendering.com/resources/shaderx/Tips_and_Tricks_with_DirectX_9.pdf)
- [GPU Gems](https://developer.nvidia.com/gpugems/gpugems2/part-i-geometric-complexity/chapter-7-adaptive-tessellation-subdivision-surfaces)