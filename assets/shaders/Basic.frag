#version 450 core

/* Variables */

layout(location = 0) in float iTessLevel;

layout(location = 0) out vec4 oColour;

/* Functions */

void main() { 
    float maxDepth = 8.0;
    float color = iTessLevel / maxDepth;
    oColour.rgb = vec3(color);
}
