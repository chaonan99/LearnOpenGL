#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D ssao;

struct Light {
    vec3 Position;
    vec3 Color;
    float Constant;
    float Linear;
    float Quadratic;
};
uniform Light light;
uniform int draw_mode;

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedo, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    float Specular = texture(gAlbedo, TexCoords).a;
    float AmbientOcclusion = texture(ssao, TexCoords).r;
    vec3 lighting = Albedo * AmbientOcclusion * 0.3; // hard-coded ambient component
    vec3 viewDir = normalize(-FragPos);

    // Diffuse
    vec3 lightDir = normalize(light.Position - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * light.Color;
    // Specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0);
    vec3 specular = light.Color * spec;
    float distance    = length(light.Position - FragPos);
    float attenuation = 1.0f / (light.Constant + light.Linear * distance +
             light.Quadratic * (distance * distance));
    lighting += (diffuse * attenuation);
    lighting += (specular * attenuation);
    // FragColor = vec4(lighting, 1.0f);

    if(draw_mode == 1)
        FragColor = vec4(lighting, 1.0);
    else if(draw_mode == 2)
        FragColor = vec4(FragPos, 1.0);
     else if(draw_mode == 3)
        FragColor = vec4(Normal, 1.0);
    else if(draw_mode == 4)
        FragColor = vec4(vec3(AmbientOcclusion), 1.0);
}