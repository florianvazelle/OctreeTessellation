#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main(void) {
  gl_Position = u_projectionMatrix * (u_viewMatrix * (u_modelMatrix * vec4(a_position, 1.0)));
}