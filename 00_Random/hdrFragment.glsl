// #version 330 core
// out vec4 color;
// in vec2 TexCoords;

// uniform sampler2D hdrBuffer;
// uniform float exposure;
// uniform bool hdr;

// void main()
// {
//     vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
//     if (hdr)
//     {
//         const float gamma = 2.2;
//         // Reinhard tone mapping
//         vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
//         // Gamma correction
//         mapped = pow(mapped, vec3(1.0 / gamma));
//         color = vec4(mapped, 1.0);
//         // color = vec4(1.0f, 0.0, 1.0f, 1.0f);
//     }
//     else
//         color = vec4(hdrColor, 1.0);
// }

#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform float exposure;

void main()
{
    const float gamma = 2.2;
    vec3 hdrColor = texture(scene, TexCoords).rgb;
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0f);
}