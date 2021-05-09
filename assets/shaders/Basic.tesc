#version 450 core

// The number of vertices in the output patch is defined with an output layout qualifier:
layout(vertices = 3) out;

in float vertTessLevel[];
out float tescTessLevel[];

void main() {
  // Pass along the vertex position unmodified
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  tescTessLevel[gl_InvocationID] = vertTessLevel[gl_InvocationID];

  float tessLevel = 1.0;

  // Set built-in patch output variables
  gl_TessLevelOuter[0] = vertTessLevel[0];
  gl_TessLevelOuter[1] = vertTessLevel[1];
  gl_TessLevelOuter[2] = vertTessLevel[2];

  gl_TessLevelInner[0] = tessLevel;
}