#include <Application.hpp>
#include <Window.hpp>

#include <iostream>

static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
  const char* _source;
  const char* _type;
  const char* _severity;

  if (type == GL_DEBUG_TYPE_ERROR) _type = "ERROR";
  else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) _type = "DEPRECATED BEHAVIOR";
  else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) _type = "UNDEFINED BEHAVIOR";
  else if(type == GL_DEBUG_TYPE_PORTABILITY) _type = "PORTABILITY";
  else if(type == GL_DEBUG_TYPE_PERFORMANCE) _type = "PERFORMANCE";
  else if(type == GL_DEBUG_TYPE_OTHER) _type = "OTHER";
  else if(type == GL_DEBUG_TYPE_MARKER) _type = "MARKER";
  else _type = "UNKNOWN";

  if (severity == GL_DEBUG_SEVERITY_HIGH) _severity = "HIGH";
  else if(severity == GL_DEBUG_SEVERITY_MEDIUM) _severity = "MEDIUM";
  else if(severity == GL_DEBUG_SEVERITY_LOW) _severity = "LOW";
  else if(severity == GL_DEBUG_SEVERITY_NOTIFICATION) _severity = "NOTIFICATION";
  else _severity = "UNKNOWN";

  fprintf(stderr, "GL CALLBACK: type = %s, severity = %s, message = %s\n", _type, _severity, message);
}

Window::Window() : m_window(nullptr) {}

Window::Window(int width, int height, const char* title) : Window() {
  // Initialize the library
  if (!glfwInit()) throw std::runtime_error("We cannot initialize GLFW!");

  // Create a windowed mode window and its OpenGL context
  m_window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!m_window) {
    throw std::runtime_error("We cannot create GLFW Window!");
  }

  // Make the window's context current
  glfwMakeContextCurrent(m_window);

  /* Initialize OpenGL */

  {
    GLenum error = glewInit();

    if (error != GLEW_OK) {
      throw std::runtime_error("We cannot initialize GLEW!");
    }

    std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
  }

  // Set key event callback
  glfwSetKeyCallback(m_window, Window::OnKey);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);
}

Window::~Window() {
  if (m_window) glfwTerminate();
}

void Window::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));

  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, 1);
    }

    context->keyDown(key);
  } else if (action == GLFW_RELEASE) {
    context->keyUp(key);
  }
}

void Window::mainLoop() {
  while (!glfwWindowShouldClose(m_window)) {
    m_drawFrameFunc();

    // Swap front and back buffers
    glfwSwapBuffers(m_window);

    // Poll for and process events
    glfwPollEvents();
  }
}