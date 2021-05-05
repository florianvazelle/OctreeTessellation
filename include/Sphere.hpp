#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>

// https://www.songho.ca/opengl/gl_sphere.html#example_sphere
class Sphere {
 private:
  std::vector<glm::vec3> map_vertices;
  std::vector<GLuint> map_line_indices;

 public:
  Sphere() {}
  ~Sphere() {}

  inline const std::vector<glm::vec3> vertices() const { return map_vertices; }
  inline const std::vector<GLuint> indices() const { return map_line_indices; }

  void Initialize(int sectorCount, int stackCount, float radius);
};