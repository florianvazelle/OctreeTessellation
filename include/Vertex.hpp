#pragma once

struct alignas(16) Vertex {
  glm::vec3 position;
  float tessLevel;

  Vertex(float x, float y, float z) : position(x, y, z), tessLevel(1.0f) {}
  ~Vertex() {}

  static void setAttribute(const GLuint& shader) {
    int loc_position = glGetAttribLocation(shader, "a_position");
    int loc_tessLevel = glGetAttribLocation(shader, "a_tessLevel");

    // Indique que les donnees sont sous forme de tableau
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_tessLevel);

    // Specifie la structure des donnees envoyees au GPU
    glVertexAttribPointer(loc_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
    glVertexAttribPointer(loc_tessLevel, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tessLevel));
  }
};