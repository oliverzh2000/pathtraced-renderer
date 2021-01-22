#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform float samples_per_pixel;

void main()
{
	FragColor = texture(texture1, TexCoord) / samples_per_pixel;
}
