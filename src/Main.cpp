#include <Application.hpp>

#include <iostream>
#include <exception>

int main(void) try {
  Window window(1280, 720, "OpenGL Scene 3D");

  Context context(window);

  Application app(context);

  window.SetWindowUserPointer(&context);

  window.SetDrawFrameFunc([&]() {
    context.ComputeDeltaTime();

    app.Idle(context);
    app.Display(context);
  });

  window.mainLoop();

  return 0;
} catch (const std::exception& e) {
  std::cout << e.what() << std::endl;
}