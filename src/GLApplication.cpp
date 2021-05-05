#include <GLApplication.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>
#include <vector>

void GLApplication::Initialize(GLFWwindow* window) {
  /* Initialize OpenGL */

  GLenum error = glewInit();

  if (error != GLEW_OK) {
    std::cout << "erreur d'initialisation de GLEW!" << std::endl;
  }

  std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;

  /* Load basic shader */

  _basicShader.LoadShader(GL_VERTEX_SHADER, BASIC_VERT);
  // _basicShader.LoadShader(GL_TESS_CONTROL_SHADER, BASIC_TESC);
  // _basicShader.LoadShader(GL_TESS_EVALUATION_SHADER, BASIC_TESE);
  _basicShader.LoadShader(GL_FRAGMENT_SHADER, BASIC_FRAG);
  _basicShader.Create();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(0.5);

  _sphere.Initialize(72, 24, 2.0f);
}

void GLApplication::Idle() {
  double dt, dtheta = M_PI, step = 50.0;
  static double t0 = 0, t;

  dt = ((t = glfwGetTime()) - t0) / 100.0;
  t0 = t;

  if (_keyEvent.key(KLEFT))
    _cam.theta += dt * step * dtheta;
  else if (_keyEvent.key(KRIGHT))
    _cam.theta -= dt * step * dtheta;

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

  auto basic = _basicShader.GetProgram();
  glUseProgram(basic);

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
    // std::cout << _cam.x << ", " << _cam.y << ", " << _cam.z << "\n";

    float angle = 90.0f;
    float near = 0.1f;
    float far = 100.0f;
    float aspect = width / height;
    projection = glm::perspective((float)(angle * M_PI) / 180.f, aspect, near, far);
    //   projection = glm::frustum(-0.005, 0.005, -0.005 * height / width, 0.005 * height / width,
    //   0.01, 1000.0);

    glUniformMatrix4fv(glGetUniformLocation(basic, "u_modelMatrix"), 1, GL_FALSE, &(model[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(basic, "u_viewMatrix"), 1, GL_FALSE, &(view[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(basic, "u_projectionMatrix"), 1, GL_FALSE,
                       &(projection[0][0]));
  }

  /* Draw */

  {
    std::vector<glm::vec3> vertices = _sphere.vertices();
    std::vector<GLuint> indices = _sphere.indices();

    GLuint mesh;
    glGenVertexArrays(1, &mesh);
    glBindVertexArray(mesh);

    // This will identify our vertex buffer
    GLuint mesh_vbo;
    // Generate 1 buffer, put the resulting identifier in mesh_vbo
    glGenBuffers(1, &mesh_vbo);
    // The following commands will talk about our 'mesh_vbo' buffer
    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(),
                 GL_DYNAMIC_DRAW);

    /* Prepare the data for drawing through a buffer indices */
    GLuint mesh_ibo;
    glGenBuffers(1, &mesh_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(),
                 GL_DYNAMIC_DRAW);

    // Indique que les donnees sont sous forme de tableau
    glEnableVertexAttribArray(0);

    int loc_position = glGetAttribLocation(basic, "a_position");
    // Specifie la structure des donnees envoyees au GPU
    glVertexAttribPointer(loc_position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    //   glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    // unbind VBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}

void GLApplication::Shutdown() { _basicShader.Destroy(); }
