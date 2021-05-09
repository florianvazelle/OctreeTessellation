#version 450 core

/* Variables */

in float teseTessLevel;
in vec4 teseModPos;

out vec4 fragColor;

/* Functions */

void main() { 
    float maxDepth = 8.0;
    float color = teseTessLevel / maxDepth;
    fragColor = vec4(color, color, color, 1.0);
}
