#include <Sphere.hpp>
#include <cstddef>
#include <iostream>
#include <numbers>
#include <stdexcept>

Sphere::Sphere() {}

Sphere::~Sphere() {
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ibo);
}

void Sphere::Generate(int slices, int stacks) {
  assert(slices > 0 && stacks > 0);

  /* Generate vertices */

  {
    int i, j, k;
    GLdouble phi, theta, r, y;
    GLdouble c2MPI_Long = 2.0 * M_PI / slices;
    GLdouble cMPI_Lat = M_PI / stacks;

    m_vertices.resize((slices + 1) * (stacks + 1));

    for (i = 0, k = 0; i <= (int)stacks; ++i) {
      theta = -M_PI_2 + i * cMPI_Lat;
      y = sin(theta);
      r = cos(theta);
      for (j = 0; j <= (int)slices; ++j) {
        phi = j * c2MPI_Long;

        glm::vec3 position = glm::vec3(r * cos(phi), y, r * sin(phi));
        glm::vec2 texCoord = glm::vec2(phi / (2.0 * M_PI), (theta + M_PI_2) / M_PI);

        m_vertices[k++] = {position, position, texCoord, 1.0f};
      }
    }
  }

  /* Generate indices */

  {
    int width = slices + 1, height = stacks + 1;
    int z, nz, x, nx, k, zw, nzw, wm1 = width - 1, hm1 = height - 1;

    m_indices.resize(6 * wm1 * hm1);

    for (z = 0, k = 0; z < hm1; ++z) {
      nz = z + 1;
      zw = z * width;
      nzw = nz * width;
      for (x = 0; x < wm1; ++x) {
        nx = x + 1;

        m_indices[k++] = zw + x;
        m_indices[k++] = nzw + x;
        m_indices[k++] = zw + nx;

        m_indices[k++] = zw + nx;
        m_indices[k++] = nzw + x;
        m_indices[k++] = nzw + nx;
      }
    }
  }
}

void Sphere::Initialize(const GLuint& shader) {
  if (m_vertices.size() == 0 || m_indices.size() == 0) {
    throw std::logic_error("Sphere's vertices or indices are emtpy.\nDid you call Generate method before ?");
  }

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // Generate 1 buffer, put the resulting identifier in m_vbo
  glGenBuffers(1, &m_vbo);
  // The following commands will talk about our 'm_vbo' buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  // Give our m_vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

  // Prepare the data for drawing through a buffer m_indices
  glGenBuffers(1, &m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

  Vertex::setAttribute(shader);

  // Unbind
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Sphere::Draw() {
  if (m_vao == 0) {
    throw std::logic_error("Sphere's VAO is null.");
  }

  glBindVertexArray(m_vao);
  glDrawElements(GL_PATCHES, m_indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}