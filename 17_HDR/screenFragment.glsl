#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseTexture;
uniform vec3 viewPos;

struct Lighting {
    vec3 position;
    vec3 color;
};

uniform Lighting lights[4];

void main()
{
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    // Ambient
    vec3 ambient = 0.4 * color;
    // Diffuse and specular
    vec3 lighting = vec3(0.0);
    for (int i = 0; i < 4; ++ i)
    {
        vec3 lightDir = normalize(lights[i].position - fs_in.FragPos);
        float diff = max(dot(lightDir, fs_in.Normal), 0.0);
        vec3 diffuse = lights[i].color * diff * color;
        vec3 result = diffuse;
        float distance = length(fs_in.FragPos - lights[i].position);
        result *= 1.0 / (distance);
        lighting += result;
    }
    FragColor = vec4(ambient + lighting, 1.0f);
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(FragColor.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0f);
}
