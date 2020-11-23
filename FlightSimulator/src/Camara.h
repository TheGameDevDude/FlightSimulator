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
	glm::vec3 position;
	glm::vec3 direction;
	glm::quat quaternion;
	float angleX;
	float angleY;
	float angleZ;
	const float mouseSensitivity = 0.05f;
	const float speed = 5.0f;
public:
	Camara();
	Camara(glm::vec3 position, float angleX, float angleY,float angleZ);
	glm::mat4 getViewMatrix(bool useQuaternion);
	void move(Controls control, float deltaTime);
};