#pragma once

#include "entity.hpp"
#include "../math.hpp"


class Player {
public:
	Player();
	Entity entity = Entity();

	void update();

	// Rotating
	void look();
	// Movement 
	void move();

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(up, entity.rotation));
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
private:

	// Last mouse position
	glm::vec2 m_lastMousePos = { 0, 0 }; 
	// Used to stop jump when first hovering
	bool m_mouseFirstLooked = true; 
	// Mouse sensitivity
	float m_lookSpeed = 0.12f;

	// Movement speed
	float m_moveSpeed = 5.0f;
};
