// #version 330 core
// in vec3 fColor;
// out vec4 color;

// void main()
// {
//     color = vec4(fColor, 1.0);
// }

#version 330 core

out vec4 color;

void main()
{
    // color = vec4(texture(texture_diffuse1, TexCoords));
    color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}