#include <Sphere.hpp>

void Sphere::Initialize(int sectorCount, int stackCount, float radius) {
  float x, y, z, xy;  // vertex position

  float sectorStep = 2 * M_PI / sectorCount;
  float stackStep = M_PI / stackCount;
  float sectorAngle, stackAngle;

  for (int i = 0; i <= stackCount; ++i) {
    stackAngle = M_PI / 2 - i * stackStep;  // starting from M_PI/2 to -M_PI/2
    xy = radius * cosf(stackAngle);         // r * cos(u)
    z = radius * sinf(stackAngle);          // r * sin(u)

    // add (sectorCount+1) vertices per stack
    // the first and last vertices have same position and normal, but different tex coords
    for (int j = 0; j <= sectorCount; ++j) {
      sectorAngle = j * sectorStep;  // starting from 0 to 2pi

      // vertex position (x, y, z)
      x = xy * cosf(sectorAngle);  // r * cos(u) * cos(v)
      y = xy * sinf(sectorAngle);  // r * cos(u) * sin(v)
      map_vertices.push_back(glm::vec3(x, y, z));
    }
  }

  // generate CCW index list of sphere triangles
  // k1--k1+1
  // |  / |
  // | /  |
  // k2--k2+1
  std::vector<int> indices;
  std::vector<int> lineIndices;
  int k1, k2;
  for (int i = 0; i < stackCount; ++i) {
    k1 = i * (sectorCount + 1);  // beginning of current stack
    k2 = k1 + sectorCount + 1;   // beginning of next stack

    for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
      // 2 triangles per sector excluding first and last stacks
      // k1 => k2 => k1+1
      if (i != 0) {
        map_line_indices.push_back(k1);
        map_line_indices.push_back(k2);
        map_line_indices.push_back(k1 + 1);
      }

      // k1+1 => k2 => k2+1
      if (i != (stackCount - 1)) {
        map_line_indices.push_back(k1 + 1);
        map_line_indices.push_back(k2);
        map_line_indices.push_back(k2 + 1);
      }
    }
  }
}