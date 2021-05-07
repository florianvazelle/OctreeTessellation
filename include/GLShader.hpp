#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

class GLShader {
 private:
  // Va contenir la liste de nos shaders :
  // - Un Vertex Shader est execute pour chaque sommet (vertex)
  // - Un Geometry Shader est execute pour chaque primitive
  // - Un Fragment Shader est execute pour chaque "pixel" lors de la rasterization/remplissage de la
  // primitive
  std::vector<GLuint> _shaders;

  // un programme fait le liens entre Vertex Shader et Fragment Shader
  GLuint m_Program;

  void ValidateShader(GLenum status, GLuint type) const;

 public:
  GLShader() : m_Program(0) {}
  ~GLShader() {
    for (const GLuint& shader : _shaders) {
      glDetachShader(m_Program, shader);
    }

    for (const GLuint& shader : _shaders) {
      glDeleteShader(shader);
    }

    glDeleteProgram(m_Program);
  }

  inline GLuint& GetProgram() { return m_Program; }
  inline const GLuint& GetProgram() const { return m_Program; }

  void LoadShader(GLenum type, const char* filename);

  void Create();
};