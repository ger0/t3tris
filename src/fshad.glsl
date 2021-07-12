#version 330

uniform sampler2D texMap;

in vec4 iColor;
in vec2 iTexCoord;

out vec4 pixelColor;

void main(void) {
    vec4 outC = texture(texMap, iTexCoord);
 //   if (outC.r == 0.0 && outC.g == 0.0 && outC.b == 0.0) {
	pixelColor = vec4(
	    clamp(iColor.r, 0.5, 1.0),
	    clamp(iColor.g, 0.5, 1.0),
	    clamp(iColor.b, 0.5, 1.0),
	    1.0);
//    } else 
	pixelColor = outC;
}
