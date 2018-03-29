#pragma once
#include <glad/glad.h>
#include "game_level.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

const glm::vec2 PLAYER_SIZE(100, 20);

const GLfloat PLAYER_VELOCITY(500.0f);

class Game
{
public:
	std::vector<GameLevel> Levels;
	GLuint                 Level;

	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;
	Game(GLuint width,GLuint height);
	~Game();

	void Init();
	void ProcessInput(GLfloat dt);
	void Render();
	void Update(GLfloat);
	void DoCollisions();
	void ResetLevel();
	void ResetPlayer();
};