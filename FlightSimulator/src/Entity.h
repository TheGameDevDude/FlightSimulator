#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"

class Entity {
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::mat4 modelMatrix;
private:
	Model model;
public:
	Entity(Model model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	void tick();
	Model getModel();
};