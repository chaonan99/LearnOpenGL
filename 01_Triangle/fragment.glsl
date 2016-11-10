#version 330 core

in vec3 ourColor;
out vec4 color;
// uniform vec4 ourColor; // We set this variable in the OpenGL code.

// If you declare a uniform that isn't used
// anywhere in your GLSL code the compiler will
// silently remove the variable from the compiled
// version which is the cause for several frustrating errors.

void main()
{
    // color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // color = ourColor;
    color = vec4(ourColor, 1.0f);
}
