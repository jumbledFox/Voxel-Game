#include "player.hpp"
#include "../math.hpp"

#include "../window.hpp"
#include "../input/keyboard.hpp"

Player::Player() {
	entity.rotation = { 0, 90, 0 };
}

void Player::update() {
	look();
	move();
}


void Player::look() {
	if (Window::mouseMoving) {
		glm::vec2 mousePos = Window::mousePosition;

		// If its the first time the mouse is moving, stop it jolting and return
		if (m_mouseFirstLooked) {
			m_lastMousePos = mousePos;
			m_mouseFirstLooked = false;
			return;
		}

		// Rotate the player by how far the mouse moved
		glm::vec2 change = (mousePos - m_lastMousePos) * m_lookSpeed;
		entity.rotation.y += change.x;
		entity.rotation.x += change.y;
		m_lastMousePos = mousePos;

		// Snap pitch
		if (entity.rotation.x > 90.0f)
			entity.rotation.x = 90.0f;
		if (entity.rotation.x < -90.0f)
			entity.rotation.x = -90.0f;

		// Make yaw fit into 0 - 360
		entity.rotation.y = fmod(entity.rotation.y + 360.0f, 360);

		glm::vec3 direction;
		direction.x = cos(glm::radians(entity.rotation.y)) * cos(glm::radians(entity.rotation.x));
		direction.y = sin(glm::radians(entity.rotation.x));
		direction.z = sin(glm::radians(entity.rotation.y)) * cos(glm::radians(entity.rotation.x));
		front = -glm::normalize(direction);
	}
}

void Player::move() {
	
}