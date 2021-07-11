#version 330

in vec4 iColor;

out vec4 pixelColor;

void main(void) {
    pixelColor = vec4(
	clamp(iColor.r, 0.5, 1.0),
	clamp(iColor.g, 0.5, 1.0),
	clamp(iColor.b, 0.5, 1.0),
	1.0);
}
