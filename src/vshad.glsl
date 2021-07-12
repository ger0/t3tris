#version 330
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec2 texCoord;
in vec4 vertex;

out vec2 iTexCoord;

void main() {
    gl_Position = M * vertex;
    iTexCoord = texCoord;
}
