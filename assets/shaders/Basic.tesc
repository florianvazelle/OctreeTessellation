#version 450 core

#define ID gl_InvocationID

/* Variables */

layout(vertices = 3) out;

layout(location = 0) in float iTessLevel[];

layout(location = 0) out float oTessLevel[3];

/* Functions */

void main() {
  /* Pass data */

  // On passe les valeurs sans les modifiées
  gl_out[ID].gl_Position = gl_in[ID].gl_Position;
  oTessLevel[ID] = iTessLevel[ID];

  /* Update TessLevel */

  // On va vouloir gardé un unique triangle
  gl_TessLevelInner[0] = 1.0;

  // Et on split ce triangle en n triangle
  gl_TessLevelOuter[0] = iTessLevel[0];
  gl_TessLevelOuter[1] = iTessLevel[1];
  gl_TessLevelOuter[2] = iTessLevel[2];

  // gl_TessLevelInner et gl_TessLevelOuter sont les variables de sortie du patch
}