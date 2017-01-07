# Learn OpenGL
* This is my [OpenGL](https://www.opengl.org/) practise following [this tutorial](http://learnopengl.com/).
* [OpenGL wiki](https://www.opengl.org/wiki/).

## Contents
* [01 Draw a triangle](01_Triangle)
* [02 Draw texture](02_Textures)
* [03 Object transformation using GLM](03_Transformation)
* [04 Coordinate system](04_Coordinate)
* [05 Camera](05_Camera) Not fully understood. Need further investigation.
* [06 Color](06_Color) The basic configuration of light chapter.
* [07 Lighting basic](07_Lighting) Property of point light.
* [08 Multiple forms of lighting](08_MultiLighting) Including directional light, point light, spotlight.
* [09 Model loading](09_Model) Model loading using Assimp.
* [10 Blending](10_Blending) Use blending technique to represent transparent objects.
* [11 Skybox](11_Skybox) Background, reflection and refraction.
* [12 Geometry Shader](12_GShader) First step with geometry shader.
* [13 Instancing](13_Instancing) Multi-instance rendering with geometry shader.
* [14 Blinn Phong](14_Phong) Blinn Phong lighting model and Gamma correction.
* [15 Shadow](15_Shadow) First step to render shadow.
* [16 Normal and parallax mapping](16_NMapping) Improve the scene by normal mapping and parallax mapping.
* [17 HDR and blooming](17_HDR) Improved light with HDR and blooming technique.
* [18 Deferred shading](18_Deferred) Optimize complex scene with large number of lights using deferred shading/rendering.

## Packages
* [GLFW](http://www.glfw.org/download.html)
	* Provides the bare necessities required for rendering goodies to the screen for OpenGL.
	* Compiled from source using [cmake](http://www.cmake.org/cmake/resources/software.html).
* [GLEW](http://glew.sourceforge.net/index.html)
	* OpenGL Extension Wrangler Library.
	* Provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform.
* [SOIL](http://www.lonesock.net/soil.html)
	* Simple OpenGL Image Library.
	* Provides support for loading OpenGL texture from the most popular image formats.
* [GLM](http://glm.g-truc.net/0.9.5/index.html)
	* OpenGL Mathematics.
	* a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL).
* [Assimp](http://assimp.sourceforge.net/)
    * Model loading library for OpenGL.
    * Need [DirectX](https://www.microsoft.com/en-us/download/details.aspx?id=6812) to build.