#pragma once

#include <glm/glm.hpp>

class SpotLight {
public:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float cutOff;
	float outerCutOff;
	float constantValue;
	float linearValue;
	float quadraticValue;
public:
	SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float outerCutOff, float constantValue, float linearValue, float quadraticValue);
};