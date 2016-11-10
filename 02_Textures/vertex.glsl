#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord1;
layout (location = 3) in vec2 texCoord2;

out vec3 ourColor;
out vec2 TexCoord1;
out vec2 TexCoord2;

void main()
{
    gl_Position = vec4(position, 1.0f);
    ourColor = color;
    // TexCoord = texCoord;
    TexCoord1 = vec2(texCoord1.x, 1.0f - texCoord1.y);  // Flip coordinate
    TexCoord2 = vec2(texCoord2.x, 1.0f - texCoord2.y);  // Flip coordinate
}