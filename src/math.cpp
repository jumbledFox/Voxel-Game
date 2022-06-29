#include "math.hpp"

glm::mat4 createProjectionViewMatrix(const glm::vec3& position, const glm::vec3& rotation, const glm::mat4& projection)
{
	glm::mat4 view(1.0f);

	rotateMatrix(view, rotation);
	translateMatrix(view, -position);

	return projection * view;
}

glm::mat4 makeMatrixFromTransform(const glm::vec3& position, const glm::vec3& rotation) {
	glm::mat4 matrix(1.0f);

	translateMatrix(matrix, position);
	rotateMatrix(matrix, rotation);

	return matrix;
}

void rotateMatrix(glm::mat4& matrix, const glm::vec3& degrees)
{
	matrix = glm::rotate(matrix, glm::radians(degrees.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(degrees.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(degrees.z), { 0, 0, 1 });
}


void translateMatrix(glm::mat4& matrix, const glm::vec3& offset)
{
	matrix = glm::translate(matrix, offset);
}