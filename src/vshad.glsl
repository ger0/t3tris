#version 330
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec2 texCoord;
in vec4 vertex;
in vec4 normal;

out vec2 iTexCoord;
out vec3 i_normal;
out vec3 i_pos;
out vec3 lightPos;

void main() {
    gl_Position = P * V * M * vertex;

    i_normal	= normalize(mat3(transpose(inverse(V * M))) * normal.xyz);
    i_pos	= (V * M * vertex).xyz;
    iTexCoord 	= texCoord;
    lightPos 	= vec3(V * vec4(0, 1, 3, 1));
}
