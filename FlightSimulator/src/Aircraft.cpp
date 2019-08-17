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
	onLand = true;
}

void Aircraft::tick(Controls control, Camara &camara, float deltaTime) {
	control.tick();

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

	position.x += forward.x * deltaTime * 10;
	position.y += forward.y * deltaTime * 10;
	position.z += forward.z * deltaTime * 10;

	if (position.y <= 1) {
		position.y = 1;
		onLand = true;
	}
	camara.position = position;
	camara.quaternion = quaternion;
	camara.direction = forward;
}
