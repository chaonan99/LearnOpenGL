#version 330 core
in vec2 TexCoords;
out vec4 color;
uniform sampler2D texture1;

// float near = 1.0;
// float far  = 100.0;

// float LinearizeDepth(float depth)
// {
//     float z = depth * 2.0 - 1.0; // Back to NDC
//     return (2.0 * near * far) / (far + near - z * (far - near));
// }

void main()
{
    // float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    // color = vec4(vec3(depth), 1.0f);
    color = texture(texture1, TexCoords);
    // vec4 texColor = texture(texture1, TexCoords);
    // if(texColor.a < 0.1)
    //     discard;
    // color = texColor;
}