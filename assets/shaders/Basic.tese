#version 450 core

layout(triangles, equal_spacing, ccw) in;

/* Variables */

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

layout(location = 0) in float iTessLevel[];

layout(location = 0) out float oTessLevel;

/* Functions */

// Barycentric interpolation
vec4 berp(in vec4 v[3], in vec2 u) { return v[0] + u.x * (v[1] - v[0]) + u.y * (v[2] - v[0]); }

void main() {
  vec4 v[3] = {
      gl_in[0].gl_Position,
      gl_in[1].gl_Position,
      gl_in[2].gl_Position,
  };

  gl_Position = uProjectionMatrix * (uViewMatrix * (uModelMatrix * berp(v, gl_TessCoord.xy)));
  oTessLevel = iTessLevel[0];
}