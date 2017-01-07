#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D image;

// Debug mode
// void main()
// {
//     // FragColor = texture(image, TexCoords);
//     vec3 color = texture(image, TexCoords).rgb;
//     float brightness = dot(color, vec3(0.7));
//     if (brightness > 1.0f)
//         gl_FragColor = vec4(color, 1.0f);
//     else
//         gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
// }

uniform bool horizontal;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
    vec2 tex_offset = 1.0 / textureSize(image, 0);
    vec3 result = texture(image, TexCoords).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    FragColor = vec4(result, 1.0);
}