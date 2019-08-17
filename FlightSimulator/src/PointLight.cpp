#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constantValue, float linearValue, float quadraticValue) {
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constantValue = constantValue;
	this->linearValue = linearValue;
	this->quadraticValue = quadraticValue;
}
