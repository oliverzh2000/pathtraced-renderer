#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform float pixel_divisor;

// ACES tone mapping curve fit to go from HDR to LDR
// https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
vec3 ACESFilm(vec3 x)
{
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return clamp((x*(a*x + b)) / (x*(c*x + d) + e), 0.0f, 1.0f);
}

void main()
{
// 	FragColor = texture(texture1, TexCoord) / pixel_divisor;


    // Reinhardt tonemapping on rgb
//     vec3 before_mapping = (texture(texture1, TexCoord) / pixel_divisor).rgb;
//     FragColor = vec4(before_mapping / (before_mapping + vec3(1.0)), 1.0);

    // ACESFilm tonemapping on rgb
    vec3 before_mapping = (texture(texture1, TexCoord) / pixel_divisor).rgb;
    FragColor = vec4(ACESFilm(before_mapping), 1.0);

}
