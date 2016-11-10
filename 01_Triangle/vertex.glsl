// Shaders always begin with a version declaration
#version 330 core

layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 color;	// The color variable has attribute position 1

out vec3 ourColor; // Output a color to the fragment shader

void main()
{
    // gl_Position = vec4(position.x, position.y, position.z, 1.0);
    gl_Position = vec4(position, 1.0);
    ourColor = color; // Set ourColor to the input color we got from the vertex data
}

// Swizzling
// vec2 someVec;
// vec4 differentVec = someVec.xyxx;
// vec3 anotherVec = differentVec.zyw;
// vec4 otherVec = someVec.xxxx + anotherVec.yxzy;

// vec2 vect = vec2(0.5f, 0.7f);
// vec4 result = vec4(vect, 0.0f, 0.0f);
// vec4 otherResult = vec4(result.xyz, 1.0f);
