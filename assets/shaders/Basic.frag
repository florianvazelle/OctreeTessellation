#version 450 core

/* Variables */

layout(location = 0) in vec3 iNormal;
layout(location = 1) in vec2 iTexCoord;
layout(location = 2) in float iTessLevel;
layout(location = 3) in float iFactor;

layout(location = 0) out vec4 oColour;

/* Functions */

void main() { 
    vec3 color = (vec3(iFactor) + 2.);
    vec3 blue = color * vec3(0.15, 0.05, 0.75);
    vec3 green = color * vec3(0.15, 0.75, 0.05);
    oColour = vec4(mix(blue, green, iFactor), 1);
}
