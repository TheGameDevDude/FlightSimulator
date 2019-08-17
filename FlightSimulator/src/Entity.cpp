#include "Entity.h"

Entity::Entity(Model model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) {
	this->model = model;
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	modelMatrix = glm::scale(glm::mat4(1.0f), scale) *
		glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
}

void Entity::tick() {
	modelMatrix = glm::scale(glm::mat4(1.0f), scale) *
		glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
}

Model Entity::getModel() {
	return model;
}
