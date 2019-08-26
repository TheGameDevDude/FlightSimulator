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
	float ROLL_SPEED = 150.0f;
	float PITCH_SPEED = 150.0f;
	float YAW_SPEED = 30.0f;

	float CAP_GRAVITY = 5.0f;
	float CAP_THRUST = 10.0f;

	float CAP_FOR_SPEED = 70.0f;
	float GLIDESPEED = 10.0f;
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

	float gravity;
	float thrust;
	float forwardSpeed;
	float acceleration;

public:
	Aircraft(glm::vec3 position);
	void tick(Controls control, Camara &camara, float deltaTime);
private:
	void orientation(float deltaTime, Controls control);
	void move(float deltaTime, Controls control, Camara camara);
};
