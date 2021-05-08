#include <Sphere.hpp>

#include <stdexcept>
#include <cstddef>
#include <iostream>

void Sphere::Generate(int sectorCount, int stackCount, float radius) {
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
      vertices.push_back(Vertex(x, y, z));
      std::cout << x << ", " << y << ", " << z << std::endl;
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
        indices.push_back(k1);
        indices.push_back(k2);
        indices.push_back(k1 + 1);
      }

      // k1+1 => k2 => k2+1
      if (i != (stackCount - 1)) {
        indices.push_back(k1 + 1);
        indices.push_back(k2);
        indices.push_back(k2 + 1);
      }
    }
  }
}

void Sphere::Initialize(const GLuint& shader) {
  if (vertices.size() == 0 || indices.size() == 0) {
    throw std::logic_error("Sphere vertices or indices are emtpy.\nDid you call Initialize method before ?");
  }

  glGenVertexArrays(1, &mesh);
  glBindVertexArray(mesh);

  // Generate 1 buffer, put the resulting identifier in mesh_vbo
  glGenBuffers(1, &mesh_vbo);
  // The following commands will talk about our 'mesh_vbo' buffer
  glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

  // Prepare the data for drawing through a buffer indices
  GLuint mesh_ibo;
  glGenBuffers(1, &mesh_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

  Vertex::setAttribute(shader);

  // Unbind
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Sphere::Draw() {
  if (mesh == 0) {
    throw std::logic_error("Sphere's VAO is null.");
  }

  glBindVertexArray(mesh);
  glDrawElements(GL_PATCHES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}