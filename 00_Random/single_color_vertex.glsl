// #version 330 core
// layout (location = 0) in vec3 position;

// void main()
// {
//     gl_Position = projection * view * model * vec4(position, 1.0);
//     gl_PointSize = gl_Position.z;
// }

// void main()
// {
//     // gl_Position = vec4(position, 1.0f);
//     gl_Position = projection * view * model * vec4(position, 1.0f);
//     gl_PointSize = gl_Position.z;
// }

#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
// layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoords = texCoords;
}