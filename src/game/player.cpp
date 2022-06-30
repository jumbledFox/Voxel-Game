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
	}
}

void Player::move() {
	// Movement speed - multiplied by deltatime
	float speed = m_moveSpeed * Window::getDeltatime();

	// Vector that ends up being added on to the player
	glm::vec3 mov(0, 0, 0);

	// Variables that make things a lot easier - don't ask me how they work
	glm::vec2 rads = { glm::radians(entity.rotation.x),      glm::radians(entity.rotation.y) };
	glm::vec2 rads90 = { glm::radians(entity.rotation.x + 90), glm::radians(entity.rotation.y + 90) };

	// Forward
	if (Keyboard::keyHeld(GLFW_KEY_W)) {
		mov.x -= glm::cos(rads90.y) * glm::sin(rads90.x);
		mov.z -= glm::sin(rads90.y) * glm::sin(rads90.x);
		mov.y -= glm::sin(rads.x);
	}
	// Backward
	if (Keyboard::keyHeld(GLFW_KEY_S)) {
		mov.x += glm::cos(rads90.y) * glm::sin(rads90.x);
		mov.z += glm::sin(rads90.y) * glm::sin(rads90.x);
		mov.y += glm::sin(rads.x);
	}
	// Left
	if (Keyboard::keyHeld(GLFW_KEY_A)) {
		mov.x -= glm::cos(rads.y);
		mov.z -= glm::sin(rads.y);
	}
	// Right
	if (Keyboard::keyHeld(GLFW_KEY_D)) {
		mov.x += glm::cos(rads.y);
		mov.z += glm::sin(rads.y);
	}

	// Up and down
	if (Keyboard::keyHeld(GLFW_KEY_SPACE))
		mov.y += 1;
	if (Keyboard::keyHeld(GLFW_KEY_LEFT_SHIFT))
		mov.y -= 1;

	if (Keyboard::keyHeld(GLFW_KEY_LEFT_CONTROL))
		speed *= 2;

	if (mov != glm::vec3(0, 0, 0)) mov = glm::normalize(mov) * speed;

	entity.position += mov;
}