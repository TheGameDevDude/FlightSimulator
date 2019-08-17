#pragma once

#include <glm/glm.hpp>

class PointLight {
public:
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constantValue;
	float linearValue;
	float quadraticValue;
public:
	PointLight(glm::vec3 position,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constantValue,float linearValue,float quadraticValue);
};