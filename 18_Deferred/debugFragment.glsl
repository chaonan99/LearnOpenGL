#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D image;

void main()
{
    vec4 color = texture(image, TexCoords);
    FragColor = vec4(vec3(color.a), 1.0f);
}
