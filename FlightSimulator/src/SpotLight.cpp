#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float outerCutOff, float constantValue, float linearValue, float quadraticValue) {
	this->position = position;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
	this->constantValue = constantValue;
	this->linearValue = linearValue;
	this->quadraticValue = quadraticValue;
}
