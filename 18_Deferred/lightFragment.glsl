#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct Light {
    vec3 Position;
    vec3 Color;
    float Constant;
    float Linear;
    float Quadratic;
    float Radius;
};
const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;
uniform float exposure;

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    vec3 lighting = Albedo * 0.1; // hard-coded ambient component
    vec3 viewDir = normalize(viewPos - FragPos);
    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // Diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * lights[i].Color;
        float distance    = length(lights[i].Position - FragPos);
        if(distance < lights[i].Radius)
        {
            float attenuation = 1.0f / (lights[i].Constant + lights[i].Linear * distance +
                     lights[i].Quadratic * (distance * distance));
            lighting += (diffuse * attenuation);
        }
    }
    // const float gamma = 2.2;
    // vec3 result = vec3(1.0) - exp(-lighting * exposure);
    // // also gamma correct while we're at it
    // result = pow(result, vec3(1.0 / gamma));
    // FragColor = vec4(result, 1.0f);
    FragColor = vec4(lighting, 1.0f);
}