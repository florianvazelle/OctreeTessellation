#include <Application.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>
#include <vector>
#include <numbers>

#define WORK_GROUP_SIZE 128

Application::Application(Context& context) {
  /* Load shaders */

  m_computeShader.LoadShader(GL_COMPUTE_SHADER, BASIC_COMP);
  m_computeShader.Create();

  m_renderShader.LoadShader(GL_VERTEX_SHADER, BASIC_VERT);
  m_renderShader.LoadShader(GL_TESS_CONTROL_SHADER, BASIC_TESC);
  m_renderShader.LoadShader(GL_TESS_EVALUATION_SHADER, BASIC_TESE);
  m_renderShader.LoadShader(GL_FRAGMENT_SHADER, BASIC_FRAG);
  m_renderShader.Create();

  /* Initialize OpenGL stuff */

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(0.5);

  /* Generate sphere structure */

  m_sphere.Generate(72, 24);

  const GLuint& render_tess_shader = m_renderShader.GetProgram();
  m_sphere.Initialize(render_tess_shader);

  /* Generate a SSBO with the sphere vbo */

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_sphere.vbo());
}

Application::~Application() {}

void Application::Idle(Context& context) {
  const double dt = context.dt(), dtheta = std::numbers::pi, step = 50.0;

  /* Rotate camera */

  if (context.key(KLEFT))
    m_cam.theta += dt * step * dtheta;
  else if (context.key(KRIGHT))
    m_cam.theta -= dt * step * dtheta;

  /* Move camera */

  float s = std::sin(m_cam.theta);
  float c = std::cos(m_cam.theta);

  if (context.key(KFORWARD)) {
    m_cam.x -= dt * step * s;
    m_cam.z -= dt * step * c;
  } else if (context.key(KBOTTOM)) {
    m_cam.x += dt * step * s;
    m_cam.z += dt * step * c;
  }

  if (context.key(KUP)) {
    m_cam.y += dt * step;
  } else if (context.key(KDOWN)) {
    m_cam.y -= dt * step;
  }
}

void Application::Display(Context& context) {
  int width, height;
  glfwGetWindowSize(context.window(), &width, &height);
  glfwSetWindowAspectRatio(context.window(), width, height);

  /* Compute MVP matrix */

  glm::mat4 model, view, projection;

  glm::vec3 eye = glm::vec3(m_cam.x, m_cam.y, m_cam.z);
  glm::vec3 look = glm::vec3(m_cam.x - std::sin(m_cam.theta), 0.0, m_cam.z - std::cos(m_cam.theta));
  glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

  model = glm::translate(glm::scale(glm::mat4(1.0), {0.5, 0.5, 0.5}), {0, 0, -3});

  view = glm::lookAt(eye, look, up);

  float angle = 90.0f;
  float near = 0.1f;
  float far = 100.0f;
  float aspect = width / height;
  projection = glm::perspective((float)(angle * std::numbers::pi) / 180.f, aspect, near, far);

  /* Computing */

  {
    const GLuint& compute_octree_shader = m_computeShader.GetProgram();
    glUseProgram(compute_octree_shader);

    // Convert eye position (world coordinates) to model's local space
    glm::vec3 localEye = glm::inverse(model) * glm::vec4(eye, 1.0f);
    
    Ray ray;
    ray.origin = localEye;
    ray.vector = glm::normalize(-ray.origin);

    glm::vec3 impact;
    Sphere::Intersect(ray, impact); // Intersection in local space

    glUniform3fv(glGetUniformLocation(compute_octree_shader, "uImpact"), 1, &impact[0]);

    // Launch compute shader
    glDispatchCompute(m_sphere.vertices().size() / 128, 1, 1);
  }

  // Make sure writing to buffer has finished before read
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

  /* Rendering */

  {
    const GLuint& render_tess_shader = m_renderShader.GetProgram();
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

    /* Bind MVP matrix */

    {
      glUniformMatrix4fv(glGetUniformLocation(render_tess_shader, "uModelMatrix"), 1, GL_FALSE, &(model[0][0]));
      glUniformMatrix4fv(glGetUniformLocation(render_tess_shader, "uViewMatrix"), 1, GL_FALSE, &(view[0][0]));
      glUniformMatrix4fv(glGetUniformLocation(render_tess_shader, "uProjectionMatrix"), 1, GL_FALSE, &(projection[0][0]));
    }

    /* Draw */

    m_sphere.Draw();
  }
}