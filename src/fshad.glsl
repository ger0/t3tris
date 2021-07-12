#version 330

uniform sampler2D texMap;

in vec2 iTexCoord;

out vec4 pixelColor;

void main(void) {
    pixelColor = texture(texMap, iTexCoord);
}
