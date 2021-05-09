#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// enum that index keyboard mapping for direction commands
enum keys_t { KLEFT = 0, KRIGHT, KFORWARD, KBOTTOM, KUP, KDOWN };

class KeyEvent {
 private:
  // keyboard for direction commands
  GLuint m_keys[6] = {0, 0, 0, 0, 0, 0};

 public:
  KeyEvent();
  ~KeyEvent();

  /* Inline getters */

  inline GLuint key(keys_t i) const { return m_keys[i]; }

  /**
   * @brief Event call when a key is pressed
   */
  void keyUp(int keycode);

  /**
   * @brief Event call when a key is released
   */
  void keyDown(int keycode);
};
