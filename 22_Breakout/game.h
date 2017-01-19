#pragma once

#include <vector>
#include <tuple>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <irrKlang.h>

#include "resource.h"
#include "spriteReader.h"
#include "gameLevel.h"
#include "ballObject.h"
#include "particleGenerator.h"
#include "postProcessor.h"
#include "powerUp.h"
#include "textRenderer.h"

using namespace irrklang;

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class Game
{
public:
	GLuint Lives;
	GameState State;
	GLboolean Keys[1024];
	GLboolean KeysProcessed[1024];
	GLuint Width, Height;
	std::vector<GameLevel> Levels;
	GLuint Level;
	std::vector<PowerUp>  PowerUps;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// Reset function
	void ResetLevel();
	void ResetPlayer();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();
	void SpawnPowerUps(GameObject &block);
	void UpdatePowerUps(GLfloat dt);
private:
	GLboolean CheckCollisionBall(BallObject &one, GameObject &two);
	GLboolean CheckCollisionAABB(GameObject &one, GameObject &two);
	Collision CheckCollision(BallObject &one, GameObject &two);
	Direction VectorDirection(glm::vec2 target);
	void ActivatePowerUp(PowerUp &powerUp);
};