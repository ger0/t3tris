#version 330

uniform sampler2D texMap;
uniform vec3 cameraPos;

in vec3 lightPos;
in vec2 iTexCoord;
in vec3 i_normal;
in vec3 i_pos;

out vec4 pixelColor;

void main(void) {
    vec3 lightColor	= vec3(1.0, 1.0, 1.0);

// ambient
    vec4 color 		= texture(texMap, iTexCoord);
    vec3 ambient	= lightColor * 0.10;

// diffuse
    vec3 lightDir	= normalize(lightPos - i_pos);
    float i_nl 		= max(dot(i_normal, lightDir), 0.0);
    vec3 diffuse	= lightColor * i_nl;

// specular
    vec3 viewDir	= normalize(-i_pos);
    vec3 reflDir	= reflect(-lightDir, i_normal);
    float specVal	= pow(max(dot(viewDir, reflDir), 0.0), 32);
    vec3 spec		= 0.5 * specVal * lightColor;

// output
    pixelColor 		= vec4((ambient + diffuse + spec) * color.rgb, color.a);
}
