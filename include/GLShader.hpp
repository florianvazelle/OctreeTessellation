#pragma once

#include <cstdint>
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

  bool CompileShader(GLuint type);

 public:
  GLShader() : m_Program(0) {}
  ~GLShader() {}

  inline GLuint& GetProgram() { return m_Program; }
  inline const GLuint& GetProgram() const { return m_Program; }

  bool LoadShader(GLenum type, const char* filename);

  bool Create();
  void Destroy();
};