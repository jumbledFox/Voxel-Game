#pragma once

#include <glm/glm.hpp>

class Entity {
public:
	Entity(float mass = 0.1f, glm::vec3 pos = { 0.0f, 0.0f, 0.0f }, glm::vec3 rot = { 0.0f, 0.0f, 0.0f });

	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 velocity = { 0, 0, 0 };
	glm::vec3 force = { 0, 0, 0 };
	float mass;

	glm::mat4 modelMatrix;
	void updateMatrix();
};