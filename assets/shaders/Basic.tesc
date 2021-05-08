#version 450 core

// The number of vertices in the output patch is defined with an output layout qualifier:
layout(vertices = 3) out;

in float tesc_tessLevel[];
out float tese_tessLevel[];

void main() {
  // Pass along the vertex position unmodified
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  tese_tessLevel[gl_InvocationID] = tesc_tessLevel[gl_InvocationID];

  float tessLevel = 1.0;

  // Set built-in patch output variables
  gl_TessLevelOuter[0] = tesc_tessLevel[0];
  gl_TessLevelOuter[1] = tesc_tessLevel[1];
  gl_TessLevelOuter[2] = tesc_tessLevel[2];

  gl_TessLevelInner[0] = tessLevel;
}