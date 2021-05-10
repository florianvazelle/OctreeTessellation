#version 450 core

layout(triangles, equal_spacing, ccw) in;

/* Variables */

uniform mat4 uModelMatrix;

layout(location = 0) in vec3 iNormal[];
layout(location = 3) in vec2 iTexCoord[];
layout(location = 6) in float iTessLevel[];

layout(location = 0) out vec3 oNormal;
layout(location = 1) out vec2 oTexCoord;
layout(location = 2) out float oTessLevel;

/* Functions */

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2) {
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2) {
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
} 

void main() {
  vec3 position[3] = {
      gl_in[0].gl_Position.xyz,
      gl_in[1].gl_Position.xyz,
      gl_in[2].gl_Position.xyz,
  };

  vec3 ipos = interpolate3D(position[0], position[1], position[2]);
  gl_Position = vec4(ipos, 1.0);
  
  vec3 inorm = normalize(interpolate3D(iNormal[0], iNormal[1], iNormal[2]));
  oNormal = (transpose(inverse(uModelMatrix)) * vec4(inorm, 0.0)).xyz;

  oTexCoord = interpolate2D(iTexCoord[0], iTexCoord[1], iTexCoord[2]);
  oTessLevel = iTessLevel[0];
}