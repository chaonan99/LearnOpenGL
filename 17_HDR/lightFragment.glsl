#version 330 core

uniform vec3 lightColor;

void main()
{
    gl_FragColor = vec4(lightColor, 1.0f);
}