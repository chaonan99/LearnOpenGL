#version 330 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;
out vec4 color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_reflection1;
uniform samplerCube skybox;
uniform vec3 cameraPos;

// float near = 1.0;
// float far  = 100.0;

// float LinearizeDepth(float depth)
// {
//     float z = depth * 2.0 - 1.0; // Back to NDC
//     return (2.0 * near * far) / (far + near - z * (far - near));
// }

void main()
{
    // Diffuse
    vec4 diffuse_color = texture(texture_diffuse1, TexCoords);
    // float ratio = 1.00 / 1.52;
    float reflect_intensity = texture(texture_reflection1, TexCoords).r;
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    // vec3 R_refr = refract(I, normalize(Normal), ratio);
    vec4 reflect_color;
    // if(reflect_intensity > 0.1) // Only sample reflections when above a certain treshold
    reflect_color = texture(skybox, R) * reflect_intensity;
    // color = texture(skybox, R_refr) * 0.8;
    // color = reflect_color + diffuse_color;
    color = reflect_color * 2 + diffuse_color;
    // color = texture(skybox, R)
}
