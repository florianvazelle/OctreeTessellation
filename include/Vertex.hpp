#pragma once

struct Vertex {
  alignas(16) glm::vec3 position;
  alignas(16) glm::vec3 normal;
  alignas(16) glm::vec2 texCoord;
  alignas(4) float tessLevel;

  static void setAttribute(const GLuint& shader) {
    int loc_position = glGetAttribLocation(shader, "aPosition");
    int loc_normal = glGetAttribLocation(shader, "aNormal");
    int loc_texCoord = glGetAttribLocation(shader, "aTexCoord");
    int loc_tessLevel = glGetAttribLocation(shader, "aTessLevel");

    // Indique que les donnees sont sous forme de tableau
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_normal);
    glEnableVertexAttribArray(loc_texCoord);
    glEnableVertexAttribArray(loc_tessLevel);

    // Specifie la structure des donnees envoyees au GPU
    glVertexAttribPointer(loc_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
    glVertexAttribPointer(loc_normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
    glVertexAttribPointer(loc_texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoord));
    glVertexAttribPointer(loc_tessLevel, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tessLevel));
  }
};