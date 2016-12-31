#version 330 core
out vec4 color;

void main ()
{
    color = vec4(vec3(gl_FragCoord.z), 1.0f);
    // color = vec4(1.0f, 1.0f, 0.5f, 1.0f);
}