#version 450 core

#define ID gl_InvocationID

/* Variables */

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

layout(vertices = 3) out;

layout(location = 0) in vec3 iNormal[];
layout(location = 1) in vec2 iTexCoord[];

layout(location = 0) out vec3 oNormal[3];
layout(location = 3) out vec2 oTexCoord[3];

/* Functions */

float calcTessLevel() {
  const int minLevel = 1;
  const int maxLevel = 32;
  const float minDepth = 0.0;
  const float maxDepth = 2.5;

  vec4 p = uProjectionMatrix * uViewMatrix * uModelMatrix * (vec4(0, 0, 0, 1));

  float depth = clamp((abs(p.z) - minDepth)/(maxDepth - minDepth), 0.0, 1.0);
  return mix(maxLevel, minLevel, depth);
}

void main() {
  /* Pass data */

  // On passe les valeurs sans les modifiées
  gl_out[ID].gl_Position = gl_in[ID].gl_Position;
  oNormal[ID] = iNormal[ID];
  oTexCoord[ID] = iTexCoord[ID];

  /* Update TessLevel */

  float tessLevel = calcTessLevel();

  // On va vouloir gardé un unique triangle
  gl_TessLevelInner[0] = tessLevel;

  // Et on split ce triangle en n triangle
  gl_TessLevelOuter[0] = tessLevel;
  gl_TessLevelOuter[1] = tessLevel;
  gl_TessLevelOuter[2] = tessLevel;

  // gl_TessLevelInner et gl_TessLevelOuter sont les variables de sortie du patch
}