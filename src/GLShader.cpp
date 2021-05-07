#include <GLShader.hpp>

#include <GL/glew.h>

#include <fstream>
#include <iostream>	

void GLShader::ValidateShader(GLenum status, GLuint shader) const {
  GLint isValid;
  glGetShaderiv(shader, status, &isValid);

  if (!isValid) {
    std::string msg = "";

    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1) {
      char* infoLog = new char[1 + infoLen];

      glGetShaderInfoLog(shader, infoLen, NULL, infoLog);

      msg += ": ";
      for (int i = 0; i < infoLen; i++) {
        msg += infoLog[i];
      }

      delete[] infoLog;
    
      throw std::runtime_error("Shader error" + msg);
    }
  }
}

void GLShader::LoadShader(GLenum type, const char* filename) {
  // 1. Charger le fichier en memoire
  std::ifstream fin(filename, std::ios::in | std::ios::binary);
  fin.seekg(0, std::ios::end);
  uint32_t length = (uint32_t)fin.tellg();
  fin.seekg(0, std::ios::beg);
  char* buffer = nullptr;
  buffer = new char[length + 1];
  buffer[length] = '\0';
  fin.read(buffer, length);

  // 2. Creer le shader object
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &buffer, nullptr);

  // 3. Le compiler
  glCompileShader(shader);

  // 4. Nettoyer
  delete[] buffer;
  fin.close();  // non obligatoire ici

  _shaders.push_back(shader);

  // 5. Verifie le status de la compilation
  ValidateShader(GL_COMPILE_STATUS, shader);
}

void GLShader::Create() {
  m_Program = glCreateProgram();

  for (const GLuint& shader : _shaders) {
    glAttachShader(m_Program, shader);
  }

  glLinkProgram(m_Program);

  ValidateShader(GL_LINK_STATUS, m_Program);
}