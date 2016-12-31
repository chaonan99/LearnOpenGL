// #version 330 core
// layout (points) in;
// layout (triangle_strip, max_vertices = 5) out;

// in VS_OUT {
//     vec3 color;
// } gs_in[];

// out vec3 fColor;

// void build_house(vec4 position)
// {
//     gl_Position = position + vec4(-0.2f, -0.2f, 0.0f, 0.0f);    // 1:bottom-left
//     EmitVertex();
//     gl_Position = position + vec4( 0.2f, -0.2f, 0.0f, 0.0f);    // 2:bottom-right
//     EmitVertex();
//     gl_Position = position + vec4(-0.2f,  0.2f, 0.0f, 0.0f);    // 3:top-left
//     EmitVertex();
//     gl_Position = position + vec4( 0.2f,  0.2f, 0.0f, 0.0f);    // 4:top-right
//     EmitVertex();
//     gl_Position = position + vec4( 0.0f,  0.4f, 0.0f, 0.0f);    // 5:top
//     fColor = vec3(1.0f, 1.0f, 1.0f);
//     EmitVertex();
//     EndPrimitive();
// }

// void main()
// {
//     build_house(gl_in[0].gl_Position);
// }

#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.4f;

void GetLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0f) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GetLine(0);
    GetLine(1);
    GetLine(2);
}


// vec3 GetNormal()
// {
//     vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
//     vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
//     return normalize(cross(a, b));
// }

// vec4 explode(vec4 position, vec3 normal)
// {
//     float magnitude = 2.0f;
//     vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude;
//     return position + vec4(direction, 0.0f);
// }

// void main()
// {
//     vec3 normal = GetNormal();
//     gl_Position = explode(gl_in[0].gl_Position, normal);
//     TexCoords = gs_in[0].texCoords;
//     EmitVertex();
//     gl_Position = explode(gl_in[1].gl_Position, normal);
//     TexCoords = gs_in[1].texCoords;
//     EmitVertex();
//     gl_Position = explode(gl_in[2].gl_Position, normal);
//     TexCoords = gs_in[2].texCoords;
//     EmitVertex();
//     EndPrimitive();
// }
