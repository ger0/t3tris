#version 330

uniform sampler2D texMap;

in vec2 iTexCoord;
in float i_nl;

out vec4 pixelColor;

void main(void) {
    vec4 color = texture(texMap, iTexCoord);
    pixelColor = vec4(color.rgb * i_nl, color.a);
}
