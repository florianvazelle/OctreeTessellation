#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in float a_tessLevel;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out float vertTessLevel;

// #define PI 3.1415926535897932384626433832795
// #define PI180 float(PI / 180.0)
// #define MOD3 vec3(.1031, .11369, .13787)

// vec3 hash33(vec3 p3) {
//   p3 = fract(p3 * MOD3);
//   p3 += dot(p3, p3.yxz + 19.19);
//   return -1.0 + 2.0 * fract(vec3((p3.x + p3.y) * p3.z, (p3.x + p3.z) * p3.y, (p3.y + p3.z) * p3.x));
// }

// float perlinNoise(vec3 p) {
//   vec3 pi = floor(p);
//   vec3 pf = p - pi;

//   vec3 w = pf * pf * (3.0 - 2.0 * pf);

//   return mix(mix(mix(dot(pf - vec3(0, 0, 0), hash33(pi + vec3(0, 0, 0))), dot(pf - vec3(1, 0, 0), hash33(pi + vec3(1, 0, 0))), w.x),
//                  mix(dot(pf - vec3(0, 0, 1), hash33(pi + vec3(0, 0, 1))), dot(pf - vec3(1, 0, 1), hash33(pi + vec3(1, 0, 1))), w.x), w.z),
//              mix(mix(dot(pf - vec3(0, 1, 0), hash33(pi + vec3(0, 1, 0))), dot(pf - vec3(1, 1, 0), hash33(pi + vec3(1, 1, 0))), w.x),
//                  mix(dot(pf - vec3(0, 1, 1), hash33(pi + vec3(0, 1, 1))), dot(pf - vec3(1, 1, 1), hash33(pi + vec3(1, 1, 1))), w.x), w.z),
//              w.y);
// }

// float generatePlanet(float level) {
//   float lat = a_texCoord.y * 180 - 90;
//   float lon = a_texCoord.x * 360 - 90;
//   float r = cos(PI180 * lat);

//   float _x = (r * cos(PI180 * lon));
//   float _y = (sin(PI180 * lat));
//   float _z = (r * sin(PI180 * lon));

//   vec3 TexCoord = level * vec3(_x, _y, _z);
//   float color = perlinNoise(TexCoord);

//   return sin(color * 20.);
// }

void main(void) {
  // float factor = generatePlanet(8);
  // vec3 bpos = a_position + (0.04 * factor) * a_normal;
  gl_Position = vec4(a_position, 1.0);
  vertTessLevel = a_tessLevel;
}