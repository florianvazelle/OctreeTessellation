#pragma once

#include <KeyEvent.hpp>
#include <Shader.hpp>
#include <Sphere.hpp>
#include <Context.hpp>

class Application {
 private:
  Shader m_computeShader, m_renderShader;
  Sphere m_sphere;

  // a data structure for storing camera position and orientation
  struct cam_t {
    GLfloat x, y, z;
    GLfloat theta;
  };

  // the used camera
  cam_t m_cam = {0, 0, 0, 0};

  // rotation angles according to axis (0 = x, 1 = y, 2 = z)
  GLfloat rot[3] = {0, 0, 0};

 public:
  Application(Context& context);
  ~Application();

  /* Inline getters */

  inline cam_t& camera() { return m_cam; }
  inline const cam_t& camera() const { return m_cam; }

  /**
   * @brief Update the application (camera...)
   */
  void Idle(Context& context);

  /**
   * @brief Render the application
   */
  void Display(Context& context);
};