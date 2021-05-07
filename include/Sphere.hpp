#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>

#include <Vertex.hpp>

// https://www.songho.ca/opengl/gl_sphere.html#example_sphere
class Sphere {
 private:
  GLuint mesh,
      // This will identify our vertex buffer
      mesh_vbo;

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

 public:
  Sphere() {}
  ~Sphere() {
    glDeleteVertexArrays(1, &mesh);
    glDeleteBuffers(1, &mesh_vbo);
  }

  inline const GLuint& vbo() const { return mesh_vbo; }
  inline const std::vector<Vertex>& vert() const { return vertices; }

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