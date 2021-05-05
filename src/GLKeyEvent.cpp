#include <GLKeyEvent.hpp>

#include <cstdlib>
#include <iostream>

/*
 * Keycode : https://www.glfw.org/docs/3.0/group__keys.html
 */

void GLKeyEvent::keyDown(int keycode) {
  GLint v[2];
  switch (keycode) {
      /* directions */
    case 65:
      _keys[KLEFT] = 1;
      break;
    case 68:
      _keys[KRIGHT] = 1;
      break;
    case 87:
      _keys[KFORWARD] = 1;
      break;
    case 83:
      _keys[KBOTTOM] = 1;
      break;
    case 340:
      _keys[KDOWN] = 1;
      break;
    case 32:
      _keys[KUP] = 1;
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

void GLKeyEvent::keyUp(int keycode) {
  switch (keycode) {
    /* directions */
    case 65:
      _keys[KLEFT] = 0;
      break;
    case 68:
      _keys[KRIGHT] = 0;
      break;
    case 87:
      _keys[KFORWARD] = 0;
      break;
    case 83:
      _keys[KBOTTOM] = 0;
      break;
    case 340:
      _keys[KDOWN] = 0;
      break;
    case 32:
      _keys[KUP] = 0;
      break;

    /* default */
    default:
      break;
  }
}