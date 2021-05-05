#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// enum that index keyboard mapping for direction commands
enum kyes_t { KLEFT = 0, KRIGHT, KFORWARD, KBOTTOM, KUP, KDOWN };

class GLKeyEvent {
 private:
  // virtual keyboard for direction commands
  GLuint _keys[6] = {0, 0, 0, 0, 0, 0};

 public:
  GLKeyEvent() {}
  ~GLKeyEvent() {}

  inline GLuint key(kyes_t i) const { return _keys[i]; }

  void keyUp(int keycode);
  void keyDown(int keycode);
};
