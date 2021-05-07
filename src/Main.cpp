#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>

#include <GLApplication.hpp>

#define DEBUG 1

#if DEBUG
static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
  fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}
#endif

static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
  GLApplication* app = static_cast<GLApplication*>(glfwGetWindowUserPointer(window));

  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, 1);
    }

    app->keyDown(key);
  } else if (action == GLFW_RELEASE) {
    app->keyUp(key);
  }
}

int main(void) {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit()) return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1280, 720, "OpenGL Scene 3D", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  GLApplication app;
  app.Initialize(window);

  glfwSetWindowUserPointer(window, &app);
  glfwSetKeyCallback(window, onKey);

#if DEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);
#endif

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    app.Idle();
    app.Display(window);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}