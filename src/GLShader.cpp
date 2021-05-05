#include <GLShader.hpp>

#include <GL/glew.h>

#include <fstream>
#include <iostream>

bool ValidateShader(GLuint shader) {
  GLint compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled) {
    GLint infoLen = 0;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1) {
      char* infoLog = new char[1 + infoLen];

      glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
      std::cout << "Error compiling shader:" << infoLog << std::endl;

      delete[] infoLog;
    }

    // on supprime le shader object car il est inutilisable
    glDeleteShader(shader);

    return false;
  }

  return true;
}

bool GLShader::LoadShader(GLenum type, const char* filename) {
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

  // 5.
  // verifie le status de la compilation
  return ValidateShader(shader);
}

bool GLShader::Create() {
  m_Program = glCreateProgram();

  for (const GLuint& shader : _shaders) {
    glAttachShader(m_Program, shader);
  }

  glLinkProgram(m_Program);

  int32_t linked = 0;
  int32_t infoLen = 0;
  // verification du statut du linkage
  glGetProgramiv(m_Program, GL_LINK_STATUS, &linked);

  if (!linked) {
    glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1) {
      char* infoLog = new char[infoLen + 1];

      glGetProgramInfoLog(m_Program, infoLen, NULL, infoLog);
      std::cout << "Erreur de lien du programme: " << infoLog << std::endl;

      delete (infoLog);
    }

    glDeleteProgram(m_Program);

    return false;
  }

  return true;
}

void GLShader::Destroy() {
  for (const GLuint& shader : _shaders) {
    glDetachShader(m_Program, shader);
  }

  for (const GLuint& shader : _shaders) {
    glDeleteShader(shader);
  }

  glDeleteProgram(m_Program);
}