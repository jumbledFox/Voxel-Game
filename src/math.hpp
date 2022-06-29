#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 createProjectionViewMatrix(const glm::vec3& position, const glm::vec3& rotation, const glm::mat4& projection);
glm::mat4 makeMatrixFromTransform(const glm::vec3& position, const glm::vec3& rotation);

void rotateMatrix(glm::mat4& matrix, const glm::vec3& degrees);

void translateMatrix(glm::mat4& matrix, const glm::vec3& offset);