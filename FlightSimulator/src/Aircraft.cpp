#include "Aircraft.h"

Aircraft::Aircraft(glm::vec3 position) {
	this->position = position;
	pitchUp = 0.0f;
	pitchDown = 0.0f;
	rollLeft = 0.0f;
	rollRight = 0.0f;
	yawLeft = 0.0f;
	yawRight = 0.0f;

	forward = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	left = glm::vec3(-1, 0, 0);
	quaternion = glm::quat(1, 0, 0, 0);

	gravity = CAP_GRAVITY;
	thrust = 0;
	forwardSpeed = 0;
	acceleration = 0;
}

void Aircraft::tick(Controls control, Camara &camara, float deltaTime) {
	control.tick();

	orientation(deltaTime, control);
	move(deltaTime, control, camara);

	glm::vec3 pitchForward(forward.x, 0, forward.z);
	float pitch = glm::degrees(glm::acos(glm::dot(pitchForward, forward)));
	glm::vec3 rollLeft(left.x, 0, left.z);
	float roll = glm::degrees(glm::acos(glm::dot(rollLeft, left)));

	if (position.y <= 1) {
		if (pitch >= 10.0f || roll >= 10.0f || up.y < 0) {
			std::cout << "CRASH" << std::endl;
			forward = glm::vec3(0, 0, -1);
			up = glm::vec3(0, 1, 0);
			left = glm::vec3(-1, 0, 0);
			quaternion = glm::quat(1, 0, 0, 0);
			position = glm::vec3(0, 10, 35);
			gravity = CAP_GRAVITY;
			thrust = 0;
			forwardSpeed = 0;
			acceleration = 0;
		}
		position.y = 1;
		acceleration = 0;
		float yawAngle = 0;
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
		up = glm::vec3(0, 1, 0);
		left = glm::normalize(glm::vec3(left.x, 0, left.z));

		if (glm::cross(glm::normalize(left), glm::vec3(-1, 0, 0)).y >= 0) {
			yawAngle = glm::degrees(glm::acos(glm::dot(glm::vec3(-1.0f, 0.0f, 0.0f), left)));
		}

		if (glm::cross(glm::normalize(left), glm::vec3(-1, 0, 0)).y <= 0) {
			yawAngle = 360 - glm::degrees(glm::acos(glm::dot(glm::vec3(-1.0f, 0.0f, 0.0f), left)));
		}

		glm::vec3 eulerAngles(0, glm::radians(yawAngle), 0);
		quaternion = glm::quat(eulerAngles);
	}
	
	
	camara.position = position;
	camara.quaternion = quaternion;
	camara.direction = forward;

}

void Aircraft::orientation(float deltaTime,Controls control) {
	if (control.leftArrow) {
		rollLeft += 50 * deltaTime;
		if (rollLeft > ROLL_SPEED) {
			rollLeft = ROLL_SPEED;
		}
		rollRight -= 100 * deltaTime;
		if (rollRight < 0) {
			rollRight = 0.0f;
		}
	}
	else if (control.rightArrow) {
		rollRight += 50 * deltaTime;
		if (rollRight > ROLL_SPEED) {
			rollRight = ROLL_SPEED;
		}
		rollLeft -= 100 * deltaTime;
		if (rollLeft < 0) {
			rollLeft = 0.0f;
		}
	}
	else {
		rollLeft -= 100 * deltaTime;
		if (rollLeft < 0) {
			rollLeft = 0.0f;
		}
		rollRight -= 100 * deltaTime;
		if (rollRight < 0) {
			rollRight = 0.0f;
		}
	}

	if (control.upArrow) {
		pitchUp += 50 * deltaTime;
		if (pitchUp > PITCH_SPEED) {
			pitchUp = PITCH_SPEED;
		}
		pitchDown -= 100 * deltaTime;
		if (pitchDown < 0) {
			pitchDown = 0.0f;
		}
	}
	else if (control.downArrow) {
		pitchDown += 50 * deltaTime;
		if (pitchDown > PITCH_SPEED) {
			pitchDown = PITCH_SPEED;
		}

		pitchUp -= 100 * deltaTime;
		if (pitchUp < 0) {
			pitchUp = 0.0f;
		}
	}
	else {
		pitchUp -= 100 * deltaTime;
		if (pitchUp < 0) {
			pitchUp = 0.0f;
		}

		pitchDown -= 100 * deltaTime;
		if (pitchDown < 0) {
			pitchDown = 0.0f;
		}
	}

	if (control.keyA == true) {
		yawLeft += 20 * deltaTime;
		if (yawLeft > YAW_SPEED) {
			yawLeft = YAW_SPEED;
		}

		yawRight -= 50 * deltaTime;
		if (yawRight < 0) {
			yawRight = 0;
		}
	}
	else if (control.keyD == true) {
		yawRight += 20 * deltaTime;
		if (yawRight > YAW_SPEED) {
			yawRight = YAW_SPEED;
		}

		yawLeft -= 50 * deltaTime;
		if (yawLeft < 0) {
			yawLeft = 0;
		}
	}
	else {
		yawLeft -= 100 * deltaTime;
		if (yawLeft < 0) {
			yawLeft = 0;
		}

		yawRight -= 100 * deltaTime;
		if (yawRight < 0) {
			yawRight = 0;
		}
	}

	if (rollLeft > 0) {
		float rollAngle = glm::radians(deltaTime * rollLeft);
		float x = forward.x * sin(rollAngle / 2);
		float y = forward.y * sin(rollAngle / 2);
		float z = forward.z * sin(rollAngle / 2);
		float w = cos(rollAngle / 2);
		glm::quat q = glm::quat(w, x, y, z);
		quaternion *= q;
		forward = forward * q;
		up = up * q;
		left = left * q;
	}

	if (rollRight > 0) {
		float rollAngle = glm::radians(-deltaTime * rollRight);
		float x = forward.x * sin(rollAngle / 2);
		float y = forward.y * sin(rollAngle / 2);
		float z = forward.z * sin(rollAngle / 2);
		float w = cos(rollAngle / 2);
		glm::quat q = glm::quat(w, x, y, z);
		quaternion *= q;
		forward = forward * q;
		up = up * q;
		left = left * q;
	}

	if (pitchUp > 0) {
		float pitchAngle = glm::radians(deltaTime * pitchUp);
		float x = left.x * sin(pitchAngle / 2);
		float y = left.y * sin(pitchAngle / 2);
		float z = left.z * sin(pitchAngle / 2);
		float w = cos(pitchAngle / 2);
		glm::quat q = glm::quat(w, x, y, z);
		quaternion *= q;
		forward = forward * q;
		up = up * q;
		left = left * q;
	}

	if (pitchDown > 0) {
		float pitchAngle = glm::radians(-deltaTime * pitchDown);
		float x = left.x * sin(pitchAngle / 2);
		float y = left.y * sin(pitchAngle / 2);
		float z = left.z * sin(pitchAngle / 2);
		float w = cos(pitchAngle / 2);
		glm::quat q = glm::quat(w, x, y, z);
		quaternion *= q;
		forward = forward * q;
		up = up * q;
		left = left * q;
	}

	if (yawLeft > 0) {
		float yawAngle = glm::radians(-deltaTime * yawLeft);
		float x = up.x * sin(yawAngle / 2);
		float y = up.y * sin(yawAngle / 2);
		float z = up.z * sin(yawAngle / 2);
		float w = cos(yawAngle / 2);
		glm::quat q = glm::quat(w, x, y, z);
		quaternion *= q;
		forward = forward * q;
		up = up * q;
		left = left * q;
	}

	if (yawRight > 0) {
		float yawAngle = glm::radians(deltaTime * yawRight);
		float x = up.x * sin(yawAngle / 2);
		float y = up.y * sin(yawAngle / 2);
		float z = up.z * sin(yawAngle / 2);
		float w = cos(yawAngle / 2);
		glm::quat q = glm::quat(w, x, y, z);
		quaternion *= q;
		forward = forward * q;
		up = up * q;
		left = left * q;
	}
}

void Aircraft::move(float deltaTime, Controls control,Camara camara) {
	if (control.forward == true) {
		thrust += deltaTime;
		if (thrust >= CAP_THRUST) {
			thrust = CAP_THRUST;
		}

		gravity -= 0.0001f * deltaTime;
		if (gravity <= 0) {
			gravity = 0;
		}

		forwardSpeed += deltaTime;
		if (forwardSpeed >= CAP_FOR_SPEED) {
			forwardSpeed = CAP_FOR_SPEED;
		}
	}
	else {
		thrust -= 10 * deltaTime;
		if (thrust <= 0) {
			thrust = 0;
		}

		gravity += 10 * deltaTime;
		if (gravity >= CAP_GRAVITY) {
			gravity = CAP_GRAVITY;
		}

		forwardSpeed += 0.3f * acceleration * GLIDESPEED * deltaTime;
		forwardSpeed -= GLIDESPEED * deltaTime;

		if (forwardSpeed >= CAP_FOR_SPEED) {
			forwardSpeed = CAP_FOR_SPEED;
		}

		if (forwardSpeed <= 0) {
			forwardSpeed = 0;
		}
	}

	if (gravity > 0) {
		acceleration += gravity * deltaTime;
	}

	if (thrust > 0) {
		acceleration -= thrust * deltaTime;
		if (acceleration <= 0) {
			acceleration = 0;
		}
	}

	position.x += forward.x * deltaTime * forwardSpeed;
	position.y += forward.y * deltaTime * forwardSpeed;
	position.z += forward.z * deltaTime * forwardSpeed;

	position.y -= acceleration * deltaTime;


	
}
