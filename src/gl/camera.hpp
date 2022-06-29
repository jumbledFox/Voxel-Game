#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../math.hpp"

#include "../game/entity.hpp"

class Camera {
public:
	Camera(float fov, float apsectRatio);

	void updateProjView();
	void update(const Entity& entity);

	glm::mat4 getViewProjection() { return m_projectionView; }

	void setFov(float newFov) { fov = newFov; }
	void setAspectRatio(float newAspectRatio) { aspectRatio = newAspectRatio; }

private:
	// Projection matrix
	glm::mat4 m_projection{ 1.0f };
	// Projection * View matrix
	glm::mat4 m_projectionView{ 1.0f };

	// Position
	glm::vec3 m_position{0};
	glm::vec3 m_rotation{0};

	// Camera stuff
	float fov = 50.0f;
	float aspectRatio = 1.0f;
};