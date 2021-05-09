#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>

#include <Vertex.hpp>

// https://www.songho.ca/opengl/gl_sphere.html#example_sphere
class Sphere {
 private:
  GLuint m_vao, m_vbo, m_ibo;

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

 public:
  Sphere();
  ~Sphere();

  /* Inline getters */

  inline const GLuint& vbo() const { return m_vbo; }
  inline const std::vector<Vertex>& vertices() const { return m_vertices; }

  /**
   * @brief Generate vertices and indices
   */
  void Generate(int sectorCount, int stackCount, float radius);

  /**
   * @brief Create a VAO, VBO and a IBO
   */
  void Initialize(const GLuint& basic);

  /**
   * @brief Draw VAO
   */
  void Draw();
};