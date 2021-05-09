#version 450 core

layout(
    // domain on which the primitive generator will work (triangles/quads/isolines)
    triangles,
    // edges will be subdivided into segments with equal lengths
    equal_spacing,
    // emit triangles in counter-clockwise
    ccw) in;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

in float tescTessLevel[];

out float teseTessLevel;
out vec4 teseModPos;

out vec4 tesePosition;

// barycentric interpolation
vec4 berp(in vec4 v[3], in vec2 u) { return v[0] + u.x * (v[1] - v[0]) + u.y * (v[2] - v[0]); }

void main() {
  vec4 v[3] = {
      gl_in[0].gl_Position,
      gl_in[1].gl_Position,
      gl_in[2].gl_Position,
  };

  teseTessLevel = tescTessLevel[0];
  tesePosition = berp(v, gl_TessCoord.xy);
  teseModPos = u_modelMatrix * tesePosition;
  gl_Position = u_projectionMatrix * (u_viewMatrix * teseModPos);
}