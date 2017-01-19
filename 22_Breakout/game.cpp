#include "game.h"

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);
GameObject *Player;

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;
BallObject *Ball;
SpriteRenderer *Renderer;
ParticleGenerator *Particles;
PostProcessor *Effect;
GLfloat ShakeTime = 0.0f;

// Audio engine
ISoundEngine *SoundEngine = createIrrKlangDevice();

// Text renderer
TextRenderer  *Text;

Game::Game(GLuint width, GLuint height)
	: State(GAME_MENU), Keys(), KeysProcessed(), Width(width), Height(height), Lives(3)
{ }

Game::~Game()
{ }

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("sprite.vert", "sprite.frag", nullptr, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	// Blocks and background
	ResourceManager::LoadTexture("texture/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("texture/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("texture/block_solid.png", GL_FALSE, "block_solid");

	// Level
	GameLevel one; one.Load("level/one.lvl", this->Width, this->Height * 0.5);
	GameLevel two; two.Load("level/two.lvl", this->Width, this->Height * 0.5);
	GameLevel three; three.Load("level/three.lvl", this->Width, this->Height * 0.5);
	GameLevel four; four.Load("level/four.lvl", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 3;

	// Player
	ResourceManager::LoadTexture("texture/paddle.png", GL_TRUE, "paddle");
	glm::vec2 playerPosition = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPosition, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	// Ball
	ResourceManager::LoadTexture("texture/awesomeface.png", GL_TRUE, "face");
	glm::vec2 ballPosition = playerPosition + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPosition, BALL_RADIUS, glm::vec2(0, 0), ResourceManager::GetTexture("face"));

	// Particles
	ResourceManager::LoadShader("particle.vert", "particle.frag", nullptr, "particle");
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	ResourceManager::LoadTexture("texture/particle.png", GL_TRUE, "particle");
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"),
		ResourceManager::GetTexture("particle"), 500);

	// Post processor
	ResourceManager::LoadShader("postprocessing.vert", "postprocessing.frag", nullptr, "postprocessing");
	Effect = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);

	// Power up
	ResourceManager::LoadTexture("texture/powerup_speed.png", GL_FALSE, "speed");
	ResourceManager::LoadTexture("texture/powerup_sticky.png", GL_FALSE, "sticky");
	ResourceManager::LoadTexture("texture/powerup_passthrough.png", GL_FALSE, "passthrough");
	ResourceManager::LoadTexture("texture/powerup_increase.png", GL_FALSE, "increase");
	ResourceManager::LoadTexture("texture/powerup_confuse.png", GL_FALSE, "confuse");
	ResourceManager::LoadTexture("texture/powerup_chaos.png", GL_FALSE, "chaos");

	// Play background music
	SoundEngine->play2D("music/breakout.mp3", GL_TRUE);

	// Text
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("font/BuxtonSketch.ttf", 24);
}

void Game::ResetLevel()
{
	switch (this->Level)
	{
	case 0:
		this->Levels[0].Load("level/one.lvl", this->Width, this->Height * 0.5f);
		break;
	case 1:
		this->Levels[1].Load("level/two.lvl", this->Width, this->Height * 0.5f);
		break;
	case 2:
		this->Levels[2].Load("level/three.lvl", this->Width, this->Height * 0.5f);
		break;
	case 3:
		this->Levels[3].Load("level/four.lvl", this->Width, this->Height * 0.5f);
		break;
	default:
		break;
	}
	this->Lives = 3;
}

void Game::ResetPlayer()
{
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2), glm::vec2(0, 0));
}

void Game::Update(GLfloat dt)
{
	// Update objects
	Ball->Move(dt, this->Width);
	// Check for collisions
	this->DoCollisions();
	// Reset game when lose
	if (Ball->Position.y > this->Height)
	{
		--this->Lives;
		if (this->Lives == 0)
		{
			this->ResetLevel();
			this->State = GAME_MENU;
		}
		this->ResetPlayer();
	}

	// Particle
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2));

	// Shake time
	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
		{
			Effect->Shake = GL_FALSE;
		}
	}

	// Update power up
	this->UpdatePowerUps(dt);

	// Win
	if (this->State == GAME_ACTIVE && this->Levels[this->Level].IsCompleted())
	{
		this->ResetLevel();
		this->ResetPlayer();
		Effect->Chaos = GL_TRUE;
		this->State = GAME_WIN;
	}
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		if (this->Keys[GLFW_KEY_A] && Player->Position.x >= 0)
		{
			Player->Position.x -= velocity;
			if (Ball->Stuck)
				Ball->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D] && Player->Position.x <= this->Width - Player->Size.x)
		{
			Player->Position.x += velocity;
			if (Ball->Stuck)
				Ball->Position.x += velocity;
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
			Ball->Stuck = false;
			Ball->Velocity = INITIAL_BALL_VELOCITY;
		}
	}
	if (this->State == GAME_MENU)
	{
		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
		{
			this->State = GAME_ACTIVE;
			this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
		}
		if (this->Keys[GLFW_KEY_W] && !this->KeysProcessed[GLFW_KEY_W])
		{
			this->Level = (this->Level + 1) % 4;
			this->KeysProcessed[GLFW_KEY_W] = GL_TRUE;
		}
		if (this->Keys[GLFW_KEY_S] && !this->KeysProcessed[GLFW_KEY_S])
		{
			if (this->Level > 0)
				--this->Level;
			else
				this->Level = 3;
			this->KeysProcessed[GLFW_KEY_S] = GL_TRUE;
		}
	}
	if (this->State == GAME_WIN)
	{
		if (this->Keys[GLFW_KEY_ENTER])
		{
			this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
			Effect->Chaos = GL_FALSE;
			this->State = GAME_MENU;
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN)
	{
		Effect->BeginRender();
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0),
			glm::vec2(this->Width, this->Height));
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		Player->Draw(*Renderer);
		Particles->Draw();
		Ball->Draw(*Renderer);
		for (PowerUp &powerUp : this->PowerUps)
			if (!powerUp.Destroyed)
				powerUp.Draw(*Renderer);
		Effect->EndRender();
		Effect->Render(glfwGetTime());
		std::stringstream ss; ss << this->Lives;
		Text->RenderText("Lives:" + ss.str(), 5.0f, 5.0f, 1.0f);
	}
	if (this->State == GAME_MENU)
	{
		Text->RenderText("Press ENTER to start", 245.0f, Height / 2, 1.35f);
		Text->RenderText("Press W or S to select level", 255.0f, Height / 2 + 40.0f, 1.0f);
	}
	if (this->State == GAME_WIN)
	{
		Text->RenderText(
			"You WON!!!", 355.0, Height / 2 - 30.0, 1.0, glm::vec3(0.0, 1.0, 0.0)
		);
		Text->RenderText(
			"Press ENTER to retry or ESC to quit", 240.0, Height / 2 + 10.0f, 1.0, glm::vec3(1.0, 1.0, 0.0)
		);
	}
}

void Game::DoCollisions()
{
	for (GameObject &box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision))
			{
				if (!box.IsSolid)
				{
					box.Destroyed = GL_TRUE;
					this->SpawnPowerUps(box);
					SoundEngine->play2D("music/bleep.mp3", GL_FALSE);
				}
				else
				{
					ShakeTime = 0.05f;
					Effect->Shake = GL_TRUE;
					SoundEngine->play2D("music/solid.wav", GL_FALSE);
				}
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vec = std::get<2>(collision);
				if (!Ball->PassThrough || box.IsSolid)
				{
					if (dir == LEFT || dir == RIGHT)
					{
						Ball->Velocity.x = -Ball->Velocity.x;
						GLfloat penetration = Ball->Radius - std::abs(diff_vec.x);
						if (dir == LEFT)
							Ball->Position.x -= penetration;
						else
							Ball->Position.x += penetration;
					}
					else
					{
						Ball->Velocity.y = -Ball->Velocity.y;
						GLfloat penetration = Ball->Radius - std::abs(diff_vec.y);
						if (dir == UP)
							Ball->Position.y -= penetration;
						else
							Ball->Position.y += penetration;
					}
				}
			}
		}
	}

	for (PowerUp &powerUp : this->PowerUps)
	{
		if (!powerUp.Destroyed)
		{
			if (powerUp.Position.y >= this->Height)
				powerUp.Destroyed = GL_TRUE;
			if (CheckCollisionAABB(powerUp, *Player))
			{
				this->ActivatePowerUp(powerUp);
				powerUp.Destroyed = GL_TRUE;
				powerUp.Activated = GL_TRUE;
				SoundEngine->play2D("music/powerup.wav", GL_FALSE);
			}
		}
	}

	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		Ball->Stuck = Ball->Sticky;
		GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
		GLfloat distance = Ball->Position.x + Ball->Radius - centerBoard;
		GLfloat percentage = distance / (Player->Size.x / 2);
		// Then move accordingly
		GLfloat strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		// Ball->Velocity.y = -Ball->Velocity.y;
		Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
		SoundEngine->play2D("music/bleep.wav", GL_FALSE);
	}
}

GLboolean ShouldSpawn(GLuint chance)
{
	GLuint random = rand() % chance;
	return random == 0;
}
void Game::SpawnPowerUps(GameObject & block)
{
	if (ShouldSpawn(75))
		this->PowerUps.push_back(
			PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f,
				block.Position, ResourceManager::GetTexture("speed"))
		);
	if (ShouldSpawn(75))
		this->PowerUps.push_back(
			PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f,
				block.Position, ResourceManager::GetTexture("sticky"))
		);
	if (ShouldSpawn(75))
		this->PowerUps.push_back(
			PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f,
				block.Position, ResourceManager::GetTexture("passthrough"))
		);
	if (ShouldSpawn(75))
		this->PowerUps.push_back(
			PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f,
				block.Position, ResourceManager::GetTexture("increase"))
		);
	if (ShouldSpawn(15)) // Negative powerups should spawn more often
		this->PowerUps.push_back(
			PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f,
				block.Position, ResourceManager::GetTexture("confuse"))
		);
	if (ShouldSpawn(15))
		this->PowerUps.push_back(
			PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f,
				block.Position, ResourceManager::GetTexture("chaos"))
		);
}

GLboolean IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type)
{
	for (const PowerUp &powerUp : powerUps)
	{
		if (powerUp.Activated)
			if (powerUp.Type == type)
				return GL_TRUE;
	}
	return GL_FALSE;
}
void Game::UpdatePowerUps(GLfloat dt)
{
	for (PowerUp &powerUp : this->PowerUps)
	{
		powerUp.Position += powerUp.Velocity * dt;
		if (powerUp.Activated)
		{
			powerUp.Duration -= dt;

			if (powerUp.Duration <= 0.0f)
			{
				powerUp.Activated = GL_FALSE;
				if (powerUp.Type == "sticky")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
					{
						Ball->Sticky = GL_FALSE;
						Player->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "pass-through")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
					{
						Ball->PassThrough = GL_FALSE;
						Ball->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "confuse")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
					{	// Only reset if no other PowerUp of type confuse is active
						Effect->Confuse = GL_FALSE;
					}
				}
				else if (powerUp.Type == "chaos")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
					{	// Only reset if no other PowerUp of type chaos is active
						Effect->Chaos = GL_FALSE;
					}
				}
			}
		}
	}
	this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
		[](const PowerUp &powerUp) { return powerUp.Destroyed && !powerUp.Activated; }),
		this->PowerUps.end());
}

GLboolean Game::CheckCollisionBall(BallObject & one, GameObject & two)
{
	// Get center point circle first
	glm::vec2 center(one.Position + one.Radius);
	// Calculate AABB info (center, half-extents)
	glm::vec2 aabbHalfExtents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabbCenter(two.Position + aabbHalfExtents);
	glm::vec2 difference = center - aabbCenter;
	glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
	// Add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabbCenter + clamped;
	difference = closest - center;
	return glm::length(difference) < one.Radius;
}

GLboolean Game::CheckCollisionAABB(GameObject &one, GameObject &two)
{
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	return collisionX && collisionY;
}

Collision Game::CheckCollision(BallObject & one, GameObject & two)
{
	// Get center point circle first
	glm::vec2 center(one.Position + one.Radius);
	// Calculate AABB info (center, half-extents)
	glm::vec2 aabbHalfExtents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabbCenter(two.Position + aabbHalfExtents);
	glm::vec2 difference = center - aabbCenter;
	glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
	// Add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabbCenter + clamped;
	difference = closest - center;
	if (glm::length(difference) <= one.Radius)
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}

Direction Game::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

void Game::ActivatePowerUp(PowerUp & powerUp)
{
	if (powerUp.Type == "speed")
		Ball->Velocity *= 1.2f;
	else if (powerUp.Type == "sticky")
	{
		Ball->Sticky = GL_TRUE;
		Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
	}
	else if (powerUp.Type == "pass-through")
	{
		Ball->PassThrough = GL_TRUE;
		Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
	}
	else if (powerUp.Type == "pad-size-increase")
	{
		Player->Size.x += 50;
	}
	else if (powerUp.Type == "confuse")
	{
		if (!Effect->Chaos)
			Effect->Confuse = GL_TRUE; // Only activate if chaos wasn't already active
	}
	else if (powerUp.Type == "chaos")
	{
		if (!Effect->Confuse)
			Effect->Chaos = GL_TRUE;
	}
}
