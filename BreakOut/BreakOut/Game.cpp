#include "Game.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include <iostream>

SpriteRenderer *Renderer;
Game::Game(GLuint width, GLuint height)
{
	this->Width = width;
	this->Height = height;
}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	
	ResourceManager::LoadShader("sprite.vs", "sprite.fs", nullptr, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image",0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	
	Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
	
	ResourceManager::LoadTexture("../textures/awesomeface.png", GL_TRUE, "face");
}

void Game::ProcessInput(GLfloat dt)
{
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
    Texture2D tex = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(tex, glm::vec2(200, 200),glm::vec2(300, 400), 45.0f, 
		glm::vec3(0.0f, 1.0f, 0.0f));
}