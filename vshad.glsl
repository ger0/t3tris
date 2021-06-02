#version 330

uniform mat4 P;
uniform mat4 V;

in vec4 vertex;
in vec4 color;

out vec4 iColor;

void main() {
    gl_Position = vertex;
    iColor = color;
}
