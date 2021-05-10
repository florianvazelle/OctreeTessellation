#version 450 core

#define PI 3.1415926535897932384626433832795
#define PI180 float(PI / 180.0)
#define MOD3 vec3(.1031, .11369, .13787)

layout (triangles) in;

layout (triangle_strip, max_vertices = 3) out; 

/* Variables */

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

layout(location = 0) in vec3 iNormal[];
layout(location = 1) in vec2 iTexCoord[];
layout(location = 2) in float iTessLevel[];

layout(location = 0) out vec3 oNormal;
layout(location = 1) out vec2 oTexCoord;
layout(location = 2) out float oTessLevel;
layout(location = 3) out float oFactor;

/* Functions */

vec3 hash33(vec3 p3) {
  p3 = fract(p3 * MOD3);
  p3 += dot(p3, p3.yxz + 19.19);
  return -1.0 + 2.0 * fract(vec3((p3.x + p3.y) * p3.z, (p3.x + p3.z) * p3.y, (p3.y + p3.z) * p3.x));
}

float perlinNoise(vec3 p) {
  vec3 pi = floor(p);
  vec3 pf = p - pi;

  vec3 w = pf * pf * (3.0 - 2.0 * pf);

  return mix(mix(mix(dot(pf - vec3(0, 0, 0), hash33(pi + vec3(0, 0, 0))), dot(pf - vec3(1, 0, 0), hash33(pi + vec3(1, 0, 0))), w.x),
                 mix(dot(pf - vec3(0, 0, 1), hash33(pi + vec3(0, 0, 1))), dot(pf - vec3(1, 0, 1), hash33(pi + vec3(1, 0, 1))), w.x), w.z),
             mix(mix(dot(pf - vec3(0, 1, 0), hash33(pi + vec3(0, 1, 0))), dot(pf - vec3(1, 1, 0), hash33(pi + vec3(1, 1, 0))), w.x),
                 mix(dot(pf - vec3(0, 1, 1), hash33(pi + vec3(0, 1, 1))), dot(pf - vec3(1, 1, 1), hash33(pi + vec3(1, 1, 1))), w.x), w.z),
             w.y);
}

float generatePlanet(vec2 texCoord, float level) {
  float lat = texCoord.y * 180 - 90;
  float lon = texCoord.x * 360 - 90;
  float r = cos(PI180 * lat);

  float x = (r * cos(PI180 * lon));
  float y = (sin(PI180 * lat));
  float z = (r * sin(PI180 * lon));

  vec3 coord = level * vec3(x, y, z);
  float color = perlinNoise(coord);

  return sin(color * 20.);
}

void main() {
    for (int i = 0; i < gl_in.length(); ++i) {
        float factor = generatePlanet(iTexCoord[i], 1.);
        
        vec3 bpos = gl_in[i].gl_Position.xyz + (0.04 * factor) * iNormal[i];
        gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(bpos, 1.0);
        
        oNormal = iNormal[i];
        oTexCoord = iTexCoord[i];
        oTessLevel = iTessLevel[i];
        oFactor = factor;

        EmitVertex();
    }
    EndPrimitive();
}