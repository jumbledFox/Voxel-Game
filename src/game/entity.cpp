#include "entity.hpp"
#include "../math.hpp"

Entity::Entity(float mass, glm::vec3 pos, glm::vec3 rot) : mass(mass), position(pos), rotation(rot) {
	updateMatrix();
}

void Entity::updateMatrix() {
	modelMatrix = makeMatrixFromTransform(position, rotation);
}