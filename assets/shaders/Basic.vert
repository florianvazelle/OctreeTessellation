#version 450 core

/* Variables */

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTessLevel;

layout(location = 0) out vec3 oNormal;
layout(location = 1) out vec2 oTexCoord;
layout(location = 2) out float oTessLevel;

/* Functions */

void main(void) {
  gl_Position = vec4(aPosition, 1.0);
  oNormal = aNormal;
  oTexCoord = aTexCoord;
  oTessLevel = aTessLevel;
}