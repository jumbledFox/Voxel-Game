#version 330 core
out vec4 FragColor;

in float fLight;

void main() {
    FragColor = vec4(fLight, 0, 0, 1);
} 