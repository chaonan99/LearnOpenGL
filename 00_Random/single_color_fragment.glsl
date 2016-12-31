// #version 330 core
// out vec4 color;

// void main()
// {
//     ourColor = vec4(0.04, 0.58, 0.26, 1.0);
// }

// void main()
// {
//     if(gl_FragCoord.x < 400)
//         color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//     else
//         color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
// }

#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{
    color = texture(texture_diffuse1, TexCoords);
}