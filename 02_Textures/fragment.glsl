#version 330 core
in vec3 ourColor;
in vec2 TexCoord1;
in vec2 TexCoord2;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixValue;

void main()
{
    // color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
    color = mix(texture(ourTexture1, TexCoord1), texture(ourTexture2, TexCoord2), mixValue);
}