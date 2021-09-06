#version 330
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 lightDir = vec4(0,1,1,0);

in vec2 texCoord;
in vec4 vertex;
in vec4 normal;

out vec2 iTexCoord;
out float i_nl;

void main() {
    gl_Position = P * V * M * vertex;

    mat4 G = mat4(inverse(transpose(mat3(M))));
    vec4 n = normalize(V * G * normal);
    i_nl = clamp(dot(n, V * lightDir), 0.1, 1);
    iTexCoord = texCoord;
}
