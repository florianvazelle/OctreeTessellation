#include <GLApplication.hpp>

#define GLM_FORCE_RADIANS
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#define WORK_GROUP_SIZE 128

void GLApplication::Initialize(GLFWwindow* window) {
  /* Initialize OpenGL */

  GLenum error = glewInit();

  if (error != GLEW_OK) {
    std::cout << "erreur d'initialisation de GLEW!" << std::endl;
  }

  std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;

  /* Load shaders */

  _computeShader.LoadShader(GL_COMPUTE_SHADER, BASIC_COMP);
  _computeShader.Create();

  _renderShader.LoadShader(GL_VERTEX_SHADER, BASIC_VERT);
  _renderShader.LoadShader(GL_TESS_CONTROL_SHADER, BASIC_TESC);
  _renderShader.LoadShader(GL_TESS_EVALUATION_SHADER, BASIC_TESE);
  _renderShader.LoadShader(GL_FRAGMENT_SHADER, BASIC_FRAG);
  _renderShader.Create();

  /* Initialize OpenGL stuff */

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(0.5);

  /* Generate sphere structure */

  _sphere.Generate(72, 24, 1.0f);

  const GLuint& render_tess_shader = _renderShader.GetProgram();
  _sphere.Initialize(render_tess_shader);

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _sphere.vbo());
}

void GLApplication::Idle() {
  double dt, dtheta = M_PI, step = 50.0;
  static double t0 = 0, t;

  /* Compute delta time */

  dt = ((t = glfwGetTime()) - t0) / 100.0;
  t0 = t;

  /* Rotate camera */

  if (_keyEvent.key(KLEFT))
    _cam.theta += dt * step * dtheta;
  else if (_keyEvent.key(KRIGHT))
    _cam.theta -= dt * step * dtheta;

  /* Move camera */

  float s = std::sin(_cam.theta);
  float c = std::cos(_cam.theta);

  if (_keyEvent.key(KFORWARD)) {
    _cam.x -= dt * step * s;
    _cam.z -= dt * step * c;
  } else if (_keyEvent.key(KBOTTOM)) {
    _cam.x += dt * step * s;
    _cam.z += dt * step * c;
  }

  if (_keyEvent.key(KUP)) {
    _cam.y += dt * step;
  } else if (_keyEvent.key(KDOWN)) {
    _cam.y -= dt * step;
  }
}

void GLApplication::Display(GLFWwindow* window) {
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  /* Computing */

  {
    const GLuint& compute_octree_shader = _computeShader.GetProgram();
    glUseProgram(compute_octree_shader);

    // Launch compute shader
    glDispatchCompute(_sphere.vert().size() / 128, 1, 1);
  }

  // Make sure writing to buffer has finished before read
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

  /* Rendering */

  {
    const GLuint& render_tess_shader = _renderShader.GetProgram();
    glUseProgram(render_tess_shader);

    /* OpenGL Stuff */

    {
      // Enable depth test
      glEnable(GL_DEPTH_TEST);
      // Accept fragment if it closer to the camera than the former one
      glDepthFunc(GL_LESS);

      glViewport(0, 0, width, height);
      // Clear the screen
      glClearColor(0.f, 0.f, 1.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /* Compute MVP matrix */

    {
      glm::mat4 model, view, projection;

      glm::vec3 eye = glm::vec3(_cam.x, _cam.y, _cam.z);
      glm::vec3 look = glm::vec3(_cam.x - std::sin(_cam.theta), 0.0, _cam.z - std::cos(_cam.theta));
      glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

      model = glm::scale(glm::mat4(1.0), {0.5, 0.5, 0.5});

      view = glm::lookAt(eye, look, up);

      float angle = 90.0f;
      float near = 0.1f;
      float far = 100.0f;
      float aspect = width / height;
      projection = glm::perspective((float)(angle * M_PI) / 180.f, aspect, near, far);

      glUniformMatrix4fv(glGetUniformLocation(render_tess_shader, "u_modelMatrix"), 1, GL_FALSE, &(model[0][0]));
      glUniformMatrix4fv(glGetUniformLocation(render_tess_shader, "u_viewMatrix"), 1, GL_FALSE, &(view[0][0]));
      glUniformMatrix4fv(glGetUniformLocation(render_tess_shader, "u_projectionMatrix"), 1, GL_FALSE, &(projection[0][0]));
    }

    /* Draw */

    _sphere.Draw();
  }
}