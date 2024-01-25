#version 330 core

out vec4 FragColor;
in vec3 ourColor;
uniform vec4 mColor;
uniform bool type;

void main() {
    if(type)
        FragColor = vec4(ourColor, 1.0);
    else
        FragColor = mColor;
}