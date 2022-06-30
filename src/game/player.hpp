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

private:

	// Last mouse position
	glm::vec2 m_lastMousePos = { 0, 0 }; 
	// Used to stop jump when first hovering
	bool m_mouseFirstLooked = true; 
	// Mouse sensitivity
	float m_lookSpeed = 0.12f;

	// Movement speed
	float m_moveSpeed = 7.5f;
};
