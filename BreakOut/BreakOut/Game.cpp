#include "Game.h"
#include <glfw3.h>
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "ball_object.h"

SpriteRenderer *Renderer;
GameObject     *Player;
BallObject     *Ball;
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const GLfloat BALL_RADIUS = 12.5f;

Game::Game(GLuint width, GLuint height) :
	State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	ResourceManager::LoadShader("sprite.vs", "sprite.fs", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	ResourceManager::LoadTexture("../textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("../textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("../textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("../textures/block_solid.png", GL_FALSE, "block_solid");

	GameLevel one; one.Load("../levels/Standard.txt", this->Width, this->Height * 0.5);
	GameLevel two; two.Load("../levels/Bounce galore.txt", this->Width, this->Height * 0.5);
	GameLevel three; three.Load("../levels/A few small gaps.txt", this->Width, this->Height * 0.5);
	GameLevel four; four.Load("../levels/Space invader.txt", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2,
		this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
		ResourceManager::GetTexture("face"));

	Shader shader = ResourceManager::GetShader("sprite");
	Renderer =new SpriteRenderer(shader);
}

void Game::Update(GLfloat dt)
{
	Ball->Move(dt, this->Width);
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)
				Player->Position.x -= velocity;
			if (Ball->Stuck)
				Ball->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
			if (Ball->Stuck)
				Ball->Position.x += velocity;
		}
		if (this->Keys[GLFW_KEY_SPACE])
			Ball->Stuck = false;
	}
}



void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Texture2D bg = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(bg,glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		
		this->Levels[this->Level].Draw(*Renderer);
		
		Player->Draw(*Renderer);
		Ball->Draw(*Renderer);
	}
}