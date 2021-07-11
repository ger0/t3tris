#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec3 color;

in vec4 vertex;
//in vec4 color;

out vec4 iColor;

void main() {
    gl_Position = M * vertex;
    iColor = vec4(color, 1.0);
}
