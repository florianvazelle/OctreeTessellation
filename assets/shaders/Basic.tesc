#version 450 core

#define ID gl_InvocationID

/* Variables */

layout(vertices = 3) out;

layout(location = 0) in vec3 iNormal[];
layout(location = 1) in vec2 iTexCoord[];
layout(location = 2) in float iTessLevel[];

layout(location = 0) out vec3 oNormal[3];
layout(location = 3) out vec2 oTexCoord[3];
layout(location = 6) out float oTessLevel[3];

/* Functions */

void main() {
  /* Pass data */

  // On passe les valeurs sans les modifiées
  gl_out[ID].gl_Position = gl_in[ID].gl_Position;
  oNormal[ID] = iNormal[ID];
  oTexCoord[ID] = iTexCoord[ID];
  oTessLevel[ID] = iTessLevel[ID];

  /* Update TessLevel */

  // On va vouloir gardé un unique triangle
  gl_TessLevelInner[0] = iTessLevel[0];

  // Et on split ce triangle en n triangle
  gl_TessLevelOuter[0] = iTessLevel[0];
  gl_TessLevelOuter[1] = iTessLevel[1];
  gl_TessLevelOuter[2] = iTessLevel[2];

  // gl_TessLevelInner et gl_TessLevelOuter sont les variables de sortie du patch
}