#pragma once

#include <GLKeyEvent.hpp>
#include <GLShader.hpp>
#include <Sphere.hpp>

class GLApplication {
 private:
  GLKeyEvent _keyEvent;
  GLShader _computeShader, _renderShader;
  Sphere _sphere;

  // a data structure for storing camera position and orientation
  struct cam_t {
    GLfloat x, y, z;
    GLfloat theta;
  };

  // the used camera
  cam_t _cam = {0, 0, 0, 0};

  // rotation angles according to axis (0 = x, 1 = y, 2 = z)
  GLfloat rot[3] = {0, 0, 0};

 public:
  GLApplication() {}
  ~GLApplication() {}

  inline cam_t& camera() { return _cam; }
  inline const cam_t& camera() const { return _cam; }

  inline void keyDown(int keycode) { _keyEvent.keyDown(keycode); }
  inline void keyUp(int keycode) { _keyEvent.keyUp(keycode); }

  void Initialize(GLFWwindow* window);
  void Idle();
  void Display(GLFWwindow* window);
};