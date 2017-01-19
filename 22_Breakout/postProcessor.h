#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "spriteReader.h"
#include "shader.h"


// PostProcessor hosts all PostProcessing effects for the Breakout
// Game. It renders the game on a textured quad after which one can
// enable specific effects by enabling either the Confuse, Chaos or 
// Shake boolean. 
// It is required to call BeginRender() before rendering the game
// and EndRender() after rendering the game for the class to work.
class PostProcessor
{
public:
	// State
	Shader PostProcessingShader;
	Texture2D Texture;
	GLuint Width, Height;
	// Options
	GLboolean Confuse, Chaos, Shake;
	// Constructor
	PostProcessor(Shader shader, GLuint width, GLuint height);
	// Prepares the postprocessor's framebuffer operations before rendering the game
	void BeginRender();
	// Should be called after rendering the game, so it stores all the rendered data into a texture object
	void EndRender();
	// Renders the PostProcessor texture quad (as a screen-encompassing large sprite)
	void Render(GLfloat time);
private:
	// Render state
	GLuint MSFBO, FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
	GLuint RBO; // RBO is used for multisampled color buffer
	GLuint VAO;
	// Initialize quad for rendering postprocessing texture
	void initRenderData();
};