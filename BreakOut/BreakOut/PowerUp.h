#pragma once
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"


const glm::vec2 SIZE_(60, 20);

const glm::vec2 VELOCITY(0.0f, 150.0f);


class PowerUp : public GameObject
{
public:
	// PowerUp State
	std::string Type;
	GLfloat     Duration;
	GLboolean   Activated;
	// Constructor
	PowerUp(std::string type, glm::vec3 color, GLfloat duration,
		glm::vec2 position, Texture2D texture)
		: GameObject(position, SIZE_, texture, color,
		VELOCITY), Type(type), Duration(duration), Activated() { }
};