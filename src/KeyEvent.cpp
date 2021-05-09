#include <KeyEvent.hpp>

#include <cstdlib>
#include <iostream>

KeyEvent::KeyEvent() {}

KeyEvent::~KeyEvent() {}

/*
 * Keycode : https://www.glfw.org/docs/3.0/group__keys.html
 */

void KeyEvent::keyDown(int keycode) {
  GLint v[2];
  switch (keycode) {
      /* directions */
    case 65:
      m_keys[KLEFT] = 1;
      break;
    case 68:
      m_keys[KRIGHT] = 1;
      break;
    case 87:
      m_keys[KFORWARD] = 1;
      break;
    case 83:
      m_keys[KBOTTOM] = 1;
      break;
    case 340:
      m_keys[KDOWN] = 1;
      break;
    case 32:
      m_keys[KUP] = 1;
      break;

    /* when 'w' pressed, toggle between line and filled mode */
    case 90:
      glGetIntegerv(GL_POLYGON_MODE, v);
      if (v[0] == GL_FILL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(0.5);
      } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glLineWidth(1.0);
      }
      break;

    /* default */
    default:
      break;
  }
}

void KeyEvent::keyUp(int keycode) {
  switch (keycode) {
    /* directions */
    case 65:
      m_keys[KLEFT] = 0;
      break;
    case 68:
      m_keys[KRIGHT] = 0;
      break;
    case 87:
      m_keys[KFORWARD] = 0;
      break;
    case 83:
      m_keys[KBOTTOM] = 0;
      break;
    case 340:
      m_keys[KDOWN] = 0;
      break;
    case 32:
      m_keys[KUP] = 0;
      break;

    /* default */
    default:
      break;
  }
}