#version 450 core

in float frag_tessLevel;

out vec4 FragColor;

void main() { 
    float maxDepth = 8.0;
    float color = frag_tessLevel / maxDepth;
    FragColor = vec4(color, color, color, 1.0);
}
