#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>

#include <GLApplication.hpp>

static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
  GLApplication* app = static_cast<GLApplication*>(glfwGetWindowUserPointer(window));

  if (action == GLFW_PRESS) {
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
  window = glfwCreateWindow(640, 480, "OpenGL Scene 3D", NULL, NULL);
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

  while (!glfwWindowShouldClose(window)) {
    app.Idle();
    app.Display(window);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  app.Shutdown();
  glfwTerminate();
  return 0;
}