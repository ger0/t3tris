#version 330
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec3 color;

in vec2 texCoord;
in vec4 vertex;

out vec4 iColor;
out vec2 iTexCoord;

void main() {
    gl_Position = M * vertex;
    iColor = vec4(color, 1.0);
    iTexCoord = texCoord;
}
