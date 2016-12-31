// #version 330 core
// layout (location = 0) in vec2 position;
// layout (location = 1) in vec3 color;

// layout (std140) uniform Matrices
// {
//     mat4 projection;
//     mat4 view;
// };
// out VS_OUT {
//     vec3 color;
// } vs_out;
// uniform mat4 model;

// void main()
// {
//     vs_out.color = color;
//     gl_Position = projection * view * model * vec4(position, 0.0f, 1.0f);
// }

#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
// layout (location = 2) in vec2 texCoords;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    vs_out.normal = normalize(vec3(projection * vec4(normalMatrix * normal, 1.0)));
}