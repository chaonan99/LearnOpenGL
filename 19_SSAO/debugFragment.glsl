#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D image;

void main()
{
    // FragColor = texture(image, TexCoords);
    float color = texture(image, TexCoords).r;
    FragColor = vec4(vec3(color), 1.0f);
    // vec3 color = texture(image, TexCoords).rgb;
    // float brightness = dot(color, vec3(0.7));
    // if (brightness > 1.0f)
    //     gl_FragColor = vec4(color, 1.0f);
    // else
    //     gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
