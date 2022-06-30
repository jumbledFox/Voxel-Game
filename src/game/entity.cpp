#include "entity.hpp"
#include "../math.hpp"

Entity::Entity(float mass, glm::vec3 pos, glm::vec3 rot, glm::vec3 headPos) : mass(mass), position(pos), rotation(rot), headPos(headPos) {
	updateMatrix();
}

void Entity::updateMatrix() {
	modelMatrix = makeMatrixFromTransform(position, rotation);
}