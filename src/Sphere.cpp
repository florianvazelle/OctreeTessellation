#include <Sphere.hpp>

#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <numbers>

Sphere::Sphere() {}

Sphere::~Sphere() {
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ibo);
}

void Sphere::Generate(int sectorCount, int stackCount, float radius) {
  float x, y, z, xy;  // vertex position

  float sectorStep = 2 * std::numbers::pi / sectorCount;
  float stackStep = std::numbers::pi / stackCount;
  float sectorAngle, stackAngle;

  for (int i = 0; i <= stackCount; ++i) {
    stackAngle = std::numbers::pi / 2 - i * stackStep;  // starting from std::numbers::pi/2 to -std::numbers::pi/2
    xy = radius * cosf(stackAngle);         // r * cos(u)
    z = radius * sinf(stackAngle);          // r * sin(u)

    // add (sectorCount+1) m_vertices per stack
    // the first and last m_vertices have same position and normal, but different tex coords
    for (int j = 0; j <= sectorCount; ++j) {
      sectorAngle = j * sectorStep;  // starting from 0 to 2pi

      // vertex position (x, y, z)
      x = xy * cosf(sectorAngle);  // r * cos(u) * cos(v)
      y = xy * sinf(sectorAngle);  // r * cos(u) * sin(v)
      m_vertices.push_back(Vertex(x, y, z));
    }
  }

  // generate CCW index list of sphere triangles
  // k1--k1+1
  // |  / |
  // | /  |
  // k2--k2+1

  int k1, k2;
  for (int i = 0; i < stackCount; ++i) {
    k1 = i * (sectorCount + 1);  // beginning of current stack
    k2 = k1 + sectorCount + 1;   // beginning of next stack

    for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
      // 2 triangles per sector excluding first and last stacks
      // k1 => k2 => k1+1
      if (i != 0) {
        m_indices.push_back(k1);
        m_indices.push_back(k2);
        m_indices.push_back(k1 + 1);
      }

      // k1+1 => k2 => k2+1
      if (i != (stackCount - 1)) {
        m_indices.push_back(k1 + 1);
        m_indices.push_back(k2);
        m_indices.push_back(k2 + 1);
      }
    }
  }
}

void Sphere::Initialize(const GLuint& shader) {
  if (m_vertices.size() == 0 || m_indices.size() == 0) {
    throw std::logic_error("Sphere m_vertices or m_indices are emtpy.\nDid you call Initialize method before ?");
  }

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // Generate 1 buffer, put the resulting identifier in m_vbo
  glGenBuffers(1, &m_vbo);
  // The following commands will talk about our 'm_vbo' buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  // Give our m_vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_DYNAMIC_DRAW);

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