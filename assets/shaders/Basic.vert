#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in float a_tessLevel;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out float tesc_tessLevel;

void main(void) {
  gl_Position = vec4(a_position, 1.0);
  tesc_tessLevel = a_tessLevel;
}