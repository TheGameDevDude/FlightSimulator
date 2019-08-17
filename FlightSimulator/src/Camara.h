#pragma once

#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Controls.h"

class Camara {
public:
	glm::vec3 position;//position of the camara
	glm::vec3 direction;//direction of the camara
	glm::quat quaternion;//angles for the camara
	float angleX;//angle for rotating along the x axis
	float angleY;//angle for rotating along the y axis
	float angleZ;//angle for rotating along the z axis
	const float mouseSensitivity = 0.05f;//for mouse input
	const float speed = 5.0f;//for moving the camara
public:
	Camara();
	Camara(glm::vec3 position, float angleX, float angleY,float angleZ);
	glm::mat4 getViewMatrix(bool useQuaternion) const;
	void move(Controls control, float deltaTime);
};