#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform float pixel_divisor;

void main()
{
	FragColor = texture(texture1, TexCoord) / pixel_divisor;
}
