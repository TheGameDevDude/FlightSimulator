#pragma once

#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#include "Model.h"
#include "Camara.h"

class Aircraft {
public:
	glm::vec3 position;
	float ROLL_SPEED = 100.0f;
	float PITCH_SPEED = 100.0f;
	float YAW_SPEED = 30.0f;
private:
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 left;
	glm::quat quaternion;

	float pitchUp;
	float pitchDown;
	float rollLeft;
	float rollRight;
	float yawLeft;
	float yawRight;

	bool onLand;
public:
	Aircraft(glm::vec3 position);
	void tick(Controls control, Camara &camara, float deltaTime);
};
